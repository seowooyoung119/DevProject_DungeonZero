// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_UI/Inventory/DZInventoryUI.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "FOR_COMMON/SECTION_LOG/UI/Inventory/DZInventoryUILOG.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZInventoryChannel.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/A_Master/DZInventoryMasterComponent.h"
#include "FOR_INGAME/SECTION_UI/Inventory/DZInventorySlotUI.h"
#include "FOR_LIBRARY/Getter/DZGetControllerLibrary.h"

//======================================================================================================================
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

void UDZInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	// 1. 메시지 서브시스템 가져오기
	if (!IsValid(GetWorld())) return;
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	ListenerHandle = MessageSubsystem.RegisterListener<FDZInventoryUpdateMessage>(DZ::Inventory::DZ_INVNETORY_UPDATE, this, &ThisClass::OnInventoryUpdateMessageReceived_internal);

	// 2. 위젯 슬롯들 생성 (1프레임 여유)
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::InitializeFixedSlots_internal, 1.0f, false);
}

void UDZInventoryUI::NativeDestruct()
{
	// 타이머 및 게임 플레이 메시지 해제
	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(ListenerHandle);
	}
	
	Super::NativeDestruct();
}

#pragma endregion
//======================================================================================================================
#pragma region 게임플레이메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임플레이메시지
	//━━━━━━━━━━━━━━━━━━━━

void UDZInventoryUI::OnInventoryUpdateMessageReceived_internal(FGameplayTag Channel, const FDZInventoryUpdateMessage& Message)
{
	// 타겟 인벤토리 확인
	if (Message.ChangeInventoryType != TargetInventoryComp) return;
		
	// 오너의 인벤토리인지 확인
	if (!IsValid(GetOwningPlayer())) return;
	if (GetOwningPlayer() != UDZGetControllerLibrary::GetPlayerControllerFromComponent(Message.InventoryComp->GetOwner())) return;
  		
	// 업데이트 실시 
	if (!IsValid(Message.InventoryComp)) return;
	RefreshInventory(Message.InventoryComp->GetInventoryData());
}

#pragma endregion
//=====================================================================================================================
#pragma region 위젯업데이트API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯업데이트API
	//━━━━━━━━━━━━━━━━━━━━	

void UDZInventoryUI::InitializeFixedSlots_internal()
{
	// 위젯 체크
	if (!IsValid(InventoryGrid) || !IsValid(SlotWidgetClass)) return;
	
	// 기존 자식이 있다면 제거 (재입입 시 안전장치)
	InventoryGrid->ClearChildren();
	CachedSlotWidgets.Empty();

	// 갯수 만큼 생성 
	for (int32 i = 0; i < FixedSlotCount; ++i)
	{
		// 생성
		UUserWidget* NewSlot = CreateWidget<UUserWidget>(GetOwningPlayer(), SlotWidgetClass);
		if (!IsValid(NewSlot))
		{
			UE_LOG(DZInventoryUILog, Error, TEXT("Failed to create slot widget at index %d"), i);
			continue;
		}
		
		// 그리드 배치
		UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(NewSlot);
		if (!IsValid(GridSlot))
		{
			UE_LOG(DZInventoryUILog, Error, TEXT("Failed to add slot widget to grid at index %d"), i);
			continue;
		}
		
		GridSlot->SetRow(i / ColumnsCount);
		GridSlot->SetColumn(i % ColumnsCount);
		
		// 캐시 배열에 저장
		CachedSlotWidgets.Add(NewSlot);
		UE_LOG(DZInventoryUILog, Log, TEXT("Fixed Slot Added: %d"), i);
	}
}

void UDZInventoryUI::RefreshInventory(FDZInventoryCompData& InventoryCompData)
{
	// 위젯 체크
	if (!IsValid(InventoryGrid) || !IsValid(SlotWidgetClass)) return;

	// 인벤토리 데이터 가져오기 
	const TArray<FDZInventorySlotData>& DataArray = InventoryCompData.InventoryDataArray;
    
	// 고정된 슬롯들을 순회
	for (int32 i = 0; i < CachedSlotWidgets.Num(); ++i)
	{
		// 실제 위젯 슬롯으로 캐스팅 
		UDZInventorySlotUI* SlotUI = Cast<UDZInventorySlotUI>(CachedSlotWidgets[i]);
		if (!IsValid(SlotUI))
		{
			UE_LOG(DZInventoryUILog, Error, TEXT("Failed to cast slot widget at index %d"), i);
			continue;
		}
		
		// 유효한 배열에 접근 후 업데이트 
		if (DataArray.IsValidIndex(i)) SlotUI->UpdateSlot(DataArray[i]);
	}
}

#pragma endregion
//======================================================================================================================
