// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/A_Master/DZInventoryMasterComponent.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Invnetory/DZInventoryUpdateMSG.h"
#include "FOR_COMMON/SECTION_LOG/Item_And_Inventory/Inventory/DZInventoryLOG.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZInventoryChannel.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventoryInternalHelperLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventorySlotInternalHelperLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemCheckLibrary.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================	
#pragma region REP_API
	

	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━

void UDZInventoryMasterComponent::OnRep_InventoryData()
{
	// UI 알림  	
	if (!IsValid(GetWorld())) return;
	FDZInventoryUpdateMessage Message;
	Message.ChangeInventoryType = InventoryData.InventoryType;
	Message.InventoryComp = this;
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.BroadcastMessage(DZ::Inventory::DZ_INVNETORY_UPDATE, Message);
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클


	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━


UDZInventoryMasterComponent::UDZInventoryMasterComponent()
{
	// tick
	PrimaryComponentTick.bCanEverTick = false;
	
	// network
	SetIsReplicatedByDefault(true);
}

void UDZInventoryMasterComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION(UDZInventoryMasterComponent, InventoryData, COND_OwnerOnly);
}

void UDZInventoryMasterComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDZInventoryMasterComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


#pragma endregion
//======================================================================================================================	
#pragma region 인벤토리_외부_API
	

	//━━━━━━━━━━━━━━━━━━━━
	// 인벤토리 외부 API
	//━━━━━━━━━━━━━━━━━━━━

bool UDZInventoryMasterComponent::AddItemToInventory_Implementation(FDZItemRuntimeData InItemRuntimeData)
{
	// 오너 검증 및 서버에서 진행 중인지 판단 
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority())
	{
		UE_LOG(DZHotKeyinventoryLOG, Warning, TEXT("오너 실패 또는 서버에서 진행 안됨"))
		return false;
	}
	
	// 유효한 아이템인지 판단 
	if (UTSItemCheckLibrary::IsThisItemValid_Lib(this, InItemRuntimeData) == false)
	{
		UE_LOG(DZHotKeyinventoryLOG, Warning, TEXT("유효한 아이템인지 판단 실패"))
		return false;
	}
	
	// 이 인벤토리에 들어올 수 있는지 판단 
	if (UTSItemCheckLibrary::IsThisItemCanPlaceInThisInventory_Lib(this, InItemRuntimeData, InventoryData) == false)
	{
		UE_LOG(DZHotKeyinventoryLOG, Warning, TEXT("이 인벤토리에 들어올 수 있는지 판단 실패"))
		return false;
	}
	
	// 스택아이템인지 아닌지 판단 
	bool bIsStackItem = UTSItemCheckLibrary::IsThisITemCanStack_Lib(this,InItemRuntimeData);

	// Case: 비 스택 
	if (bIsStackItem == false) return TrayAddNoneStackItem_internal(InItemRuntimeData);
	
	// Case: 스택 
	if (bIsStackItem == true) return TrayAddStackItem_internal(InItemRuntimeData);
	
	return false;
}

bool UDZInventoryMasterComponent::RemoveItemFromInventory_Implementation(int32 TargetSlotIndex, int32 DeleteCount)
{
	// 슬롯 유효성 체크 
	if (!InventoryData.InventoryDataArray.IsValidIndex(TargetSlotIndex)) return false;
	
	// 차감 실시
	return UDZInventorySlotInternalHelperLibrary::ReduceItemFromSlot_Lib(InventoryData.InventoryDataArray[TargetSlotIndex], DeleteCount);
}

bool UDZInventoryMasterComponent::DropItemToFromInventory_Implementation(int32 TargetSlotIndex, int32 DeleteCount)
{
	
	
	
	return false;
}

bool UDZInventoryMasterComponent::SwapItemFromThisInventoryToAnotherInventory_Implementation(FDZItemRuntimeData InItemRuntimeData)
{
	
	
	
	return false;
}



#pragma endregion
//======================================================================================================================	
#pragma region 인벤토리_내부_API
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인벤토리 내부 API
	//━━━━━━━━━━━━━━━━━━━━

	//--------------------
	// 아이템 습득 
	//-------------------
	
bool UDZInventoryMasterComponent::TrayAddNoneStackItem_internal(FDZItemRuntimeData& InItemRuntimeData)
{
	// 빈 슬롯 찾기 (배열 인덱스는 0부터 시작하므로 0보다 작을 수 없음) 
	int32 FoundSlotIndex = UDZInventoryInternalHelperLibrary::FindEmptySlot_Lib(this, InventoryData, InItemRuntimeData);
	if (FoundSlotIndex < 0) return false;

	// 인덱스 검증
	if (!InventoryData.InventoryDataArray.IsValidIndex(FoundSlotIndex)) return false;

	// 빈 슬롯에 넣기 	
	return UDZInventoryInternalHelperLibrary::AddItemToEmptySlot_Lib(this, InventoryData.InventoryDataArray[FoundSlotIndex], InItemRuntimeData);
}

bool UDZInventoryMasterComponent::TrayAddStackItem_internal(FDZItemRuntimeData& InItemRuntimeData)
{
	// 스택 가능한 슬롯 찾기 (배열 인덱스는 0부터 시작하므로 0보다 작을 수 없음)
	int32 FoundSlotIndex = UDZInventoryInternalHelperLibrary::FindStackSlot_Lib(this, InventoryData, InItemRuntimeData);
	if (FoundSlotIndex >= 0)
	{
		// 인덱스 검증
		if (!InventoryData.InventoryDataArray.IsValidIndex(FoundSlotIndex)) return false;
	
		// 스택 슬롯에 넣기
		return UDZInventoryInternalHelperLibrary::AddItemToStackSlot_Lib(this, InventoryData.InventoryDataArray[FoundSlotIndex], InItemRuntimeData);
	}
	// 스택 못 찾았을 경우 빈 슬롯에 넣기 시도
	else
	{
		return TrayAddNoneStackItem_internal(InItemRuntimeData);
	}
}

#pragma endregion
//======================================================================================================================	
	