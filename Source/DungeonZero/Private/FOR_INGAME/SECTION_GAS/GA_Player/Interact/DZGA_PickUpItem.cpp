// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player/Interact/DZGA_PickUpItem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Invnetory/DZInventoryUpdateMSG.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Interact/DZInteractTag.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZInventoryChannel.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/BodyEquip/DZBodyEquipVisualComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/BodyEquip/DZBodyEquipInventoryComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Interface/DZItemInterface.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"
#include "FOR_INGAME/SECTION_STAGE/System/Item/DZRegisterLevelPlacedItemHelperSystem.h"
#include "GameFramework/GameplayMessageSubsystem.h"

UDZGA_PickUpItem::UDZGA_PickUpItem()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Interact::DZ_INTERACT_PICKUPITEM);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Interact::DZ_INTERACT_PICKUPITEM);
	
	// 트리커 설정
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = DZ::Interact::DZ_INTERACT_PICKUPITEM;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;

	// 트리거 추가
	AbilityTriggers.Add(TriggerData);
	
}

void UDZGA_PickUpItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!TriggerEventData) { K2_EndAbility(); return; }
	
	// 실제 상호작용 로직 (서버에서만 실행)
	if (GetAvatarActorFromActorInfo()->HasAuthority() && IsValid(TriggerEventData->Target))
	{
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 타겟 const 제거
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		// 캐스팅 후 const 제거
		const ADZItemActorBase* ConstTargetItem = CastChecked<ADZItemActorBase>(TriggerEventData->Target);
		if (!IsValid(ConstTargetItem)) { K2_EndAbility(); return; }
		ADZItemActorBase* TargetItem = const_cast<ADZItemActorBase*>(ConstTargetItem);
		if (!IsValid(TargetItem)) { K2_EndAbility(); return; }
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 아이템 데이터 가져오기
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		// 아이템 인터페이스 확인 
		IDZItemInterface* ItemInterface = CastChecked<IDZItemInterface>(TargetItem);
		if (!ItemInterface) { K2_EndAbility(); return; }
		
		// 아이템 데이터 가져오기 (레퍼런스)
		FDZItemRuntimeData& ItemRuntimeData = ItemInterface->GetItemRuntimeDataPtr();
		
		// 정적 데이터 가져오기
		UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
		if (!IsValid(ItemDataSubSystem)) { K2_EndAbility(); return; }
		FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(ItemRuntimeData.StaticDataID);
		if (!ItemStaticData) { K2_EndAbility(); return; }

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 타입에 맞는 인벤토리에 넣기
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		// 플레이어 체크
		if (!IsValid(GetAvatarActorFromActorInfo())) { K2_EndAbility(); return; } 
		
		// 가능한 인벤토리 타입 순회
		TArray<EDZInventoryCompType> TempInventoryCompType = ItemStaticData->ItemStaticInfo.MatchInventoryCompType;
		for (EDZInventoryCompType InventoryCompType : TempInventoryCompType)
		{
			switch (InventoryCompType)
			{
			case EDZInventoryCompType::None:
				break;
				
			case EDZInventoryCompType::PlayerHotKey:
				AddItemToInventory_internal(ItemRuntimeData, TargetItem, *ItemStaticData);
				break;
				
			case EDZInventoryCompType::PlayerBody:
				AddItemToBody_internal(ItemRuntimeData, TargetItem, *ItemStaticData);
				break;
			}
		}
		
		K2_EndAbility();
	}
}

bool UDZGA_PickUpItem::AddItemToInventory_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck)
{
	// 플레이어 핫키 인벤토리 가져오기
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent = IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(HotKeyInventoryComponent)){ K2_EndAbility(); return false; } 
				
	// 아이템 넣기 시도 
	bool IsSuccess = IDZInventoryCompActionInterface::Execute_AddItemToInventory(HotKeyInventoryComponent, ItemRunTimeData);
	if (!IsSuccess) { K2_EndAbility(); return false; } 
					
	// 성공시 타겟 처리 
	// CASE A : 레벨에 배치된 경우 -> 원래 아이템 스택 카운트 (1) 다시 주고 숨김처리
	// CASE B : 버려진 아이템인 경우 -> 파괴철
	if (!IsValid(TargetItem)) return false;
	UDZRegisterLevelPlacedItemHelperSystem* LevelPlacedItemHelperSystem = UDZRegisterLevelPlacedItemHelperSystem::Get(GetWorld());
	if (!IsValid(LevelPlacedItemHelperSystem)) return false;
	if (LevelPlacedItemHelperSystem->IsThisItemPlaced(TargetItem) == true)
	{
		ItemRunTimeData.DynamicData.CurrentStack = 1;
		IDZCommonPlayRoleInterface::Execute_ToggleHiddenInGame(TargetItem, false, false);
	}
	else
	{
		TargetItem->Destroy();
	}
	
	// 호스트 전용 (UI 알림 -> 클라는 OnRep에서 호출)
	FDZInventoryUpdateMessage Message;
	Message.ChangeInventoryType = HotKeyInventoryComponent->GetInventoryData().InventoryType;
	Message.InventoryComp = HotKeyInventoryComponent;
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.BroadcastMessage(DZ::Inventory::DZ_INVNETORY_UPDATE, Message);
	
	return true;
}

bool UDZGA_PickUpItem::AddItemToBody_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck)
{
	// 플레이어 장비 인벤토리 가져오기
	UDZBodyEquipInventoryComponent* BodyEquipInventoryComponent = IPlayerCompGetterInterface::Execute_GetBodyEquipInventoryComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(BodyEquipInventoryComponent)){ K2_EndAbility(); return false; } 
				
	// 아이템 넣기 시도 
	bool IsSuccess = IDZInventoryCompActionInterface::Execute_AddItemToInventory(BodyEquipInventoryComponent, ItemRunTimeData);
	if (!IsSuccess) { K2_EndAbility(); return false; }
					
	// 성공시 타겟 처리 
	// CASE A : 레벨에 배치된 경우 -> 원래 아이템 스택 카운트 (1) 다시 주고 숨김처리
	// CASE B : 버려진 아이템인 경우 -> 파괴철
	if (!IsValid(TargetItem)) return false;
	UDZRegisterLevelPlacedItemHelperSystem* LevelPlacedItemHelperSystem = UDZRegisterLevelPlacedItemHelperSystem::Get(GetWorld());
	if (!IsValid(LevelPlacedItemHelperSystem)) return false;
	if (LevelPlacedItemHelperSystem->IsThisItemPlaced(TargetItem) == true)
	{
		ItemRunTimeData.DynamicData.CurrentStack = 1;
		IDZCommonPlayRoleInterface::Execute_ToggleHiddenInGame(TargetItem, false, false);
	}
	else
	{
		TargetItem->Destroy();
	}	
	
	// 장비 비주얼 업데이트
	UDZBodyEquipVisualComponent* BodyEquipVisualComponent = IPlayerCompGetterInterface::Execute_GetBodyEquipVisualComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(BodyEquipVisualComponent)){ K2_EndAbility(); return false; }
	BodyEquipVisualComponent->HandleVisual(ItemStaticDataForCheck.ItemStaticInfo.MatchInventorySlotType);
	
	// 호스트 전용 (UI 알림 -> 클라는 OnRep에서 호출)
	FDZInventoryUpdateMessage Message;
	Message.ChangeInventoryType = BodyEquipInventoryComponent->GetInventoryData().InventoryType;
	Message.InventoryComp = BodyEquipInventoryComponent;
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.BroadcastMessage(DZ::Inventory::DZ_INVNETORY_UPDATE, Message);
	
	return true;
}
