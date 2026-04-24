// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/BodyEquip/DZBodyEquipVisualComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/BodyEquip/DZBodyEquipInventoryComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventoryInternalHelperLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"


//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZBodyEquipVisualComponent::UDZBodyEquipVisualComponent()
{
	// tick
	PrimaryComponentTick.bCanEverTick = false;
	
	// network
	SetIsReplicatedByDefault(true);
}


#pragma endregion	
//======================================================================================================================	
#pragma region 장비
	
	//━━━━━━━━━━━━━━━━━━━━
	// 핫키 
	//━━━━━━━━━━━━━━━━━━━━		

void UDZBodyEquipVisualComponent::HandleVisual(TArray<EDZInventorySlotType>& InTargetSlotTypes)
{
	// 맞는 타입 가져오기 (common 은 거르고)
	EDZInventorySlotType FoundTargetSlotType = EDZInventorySlotType::None;
	for (EDZInventorySlotType& InTargetSlotType : InTargetSlotTypes)
	{
		if (InTargetSlotType == EDZInventorySlotType::Common) continue;
		FoundTargetSlotType = InTargetSlotType;
		break;
	}
	
	
	// 기존에 있는 게 있으면 지우고 붙이기. 없으면 그냥 붙이기 (장비는 갈아끼우는 형식이므로 이렇게)
	SwapSpawnVisual_internal(FoundTargetSlotType);
}

void UDZBodyEquipVisualComponent::SwapSpawnVisual_internal(EDZInventorySlotType& InTargetSlot)
{
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority()) return;
	
	// 기존꺼 일단 지우고
	HideSpawnVisual_internal(InTargetSlot);
    
	// 새 인덱스로 다시 생성
	TrySpawnVisual_internal(InTargetSlot);
}

void UDZBodyEquipVisualComponent::TrySpawnVisual_internal(EDZInventorySlotType& InTargetSlotType)
{
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority()) return;
	
	// 1. 장비 인벤토리 컴포넌트 가져오기
	UDZBodyEquipInventoryComponent* BodyEquipInventoryComponent = IPlayerCompGetterInterface::Execute_GetBodyEquipInventoryComponent(GetOwner());
	if (!IsValid(BodyEquipInventoryComponent)) return;
	
	// 2. 슬롯 유효 체크 
	FDZInventoryCompData& InventoryCompData = BodyEquipInventoryComponent->GetInventoryData();
	FDZInventorySlotData* TargetSlot = UDZInventoryInternalHelperLibrary::GetSlotDatabyType_Lib(InventoryCompData, InTargetSlotType);
	if (TargetSlot == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("장비 비주얼 슬롯 유효성 체크 실패"))
		return;
	}
	
	// 3. 정적 데이터 체크
	UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(ItemDataSubSystem)) return;
	FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(TargetSlot->ItemData.StaticDataID);
	if (ItemStaticData == nullptr) return;
	
	// 4. 맞는 타입 가져오기
	ADZItemActorBase* Value = AttachedItems.FindOrAdd(InTargetSlotType);
	
	// 5. 스폰 실시
	Value = SpawnLogic(*ItemStaticData);
}

void UDZBodyEquipVisualComponent::HideSpawnVisual_internal(EDZInventorySlotType& InTargetSlotType)
{
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority()) return;
	
	// 맞는 타입 가져오기
	TObjectPtr<ADZItemActorBase>* ValuePtr = AttachedItems.Find(InTargetSlotType);
	if (ValuePtr == nullptr) return;
	TObjectPtr<ADZItemActorBase> ActualValue = *ValuePtr;
	if (!IsValid(ActualValue)) return;

	// 파괴 후 초기화
	ActualValue->Destroy();
	ActualValue = nullptr;
}
#pragma endregion	
//======================================================================================================================		