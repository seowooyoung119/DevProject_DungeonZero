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
#include "GameFramework/GameplayMessageSubsystem.h"
#include "AbilitySystemComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventoryInternalHelperLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemCheckLibrary.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

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
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 검증
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	// 데이터, 타겟, 플레이어 체크
	if (!TriggerEventData) { K2_EndAbility(); return; }
	if (!IsValid(TriggerEventData->Target)) { K2_EndAbility(); return; }
	if (!IsValid(GetAvatarActorFromActorInfo())) { K2_EndAbility(); return; } 
		
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
	
	// 실제 상호작용 로직 (서버에서만 실행)
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		// 성공 여부 변수
		bool IsSuccess = false;
		
		// 가능한 인벤토리 타입 순회
		TArray<EDZInventoryCompType> TempInventoryCompType = ItemStaticData->ItemStaticInfo.MatchInventoryCompType;
		for (EDZInventoryCompType InventoryCompType : TempInventoryCompType)
		{
			switch (InventoryCompType)
			{
			case EDZInventoryCompType::None:
				break;
				
			case EDZInventoryCompType::PlayerHotKey:
				IsSuccess = AddItemToInventory_internal(ItemRuntimeData, TargetItem, *ItemStaticData);
				break;
				
			case EDZInventoryCompType::PlayerBody:
				IsSuccess =AddItemToBody_internal(ItemRuntimeData, TargetItem, *ItemStaticData);
				break;
			}
		}
	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 후 처리 사운드 (서버)
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
		// 게임 플레이 큐 요청
		if (IsSuccess == false) { K2_EndAbility(); return; }
		RequestAddGameplayCue(ItemRuntimeData.StaticDataID); 
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// END
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		K2_EndAbility();
		return;
		
	}
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 후 처리 사운드 (클라 및 다른 클라)
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
	{
		// 들어갈 수 있는 예측
		bool ShouldPlaySound = false;
		
		// 가능한 타입 순회
		TArray<EDZInventoryCompType> TempInventoryCompType = ItemStaticData->ItemStaticInfo.MatchInventoryCompType;
		for (EDZInventoryCompType InventoryCompType : TempInventoryCompType)
		{
			switch (InventoryCompType)
			{
			case EDZInventoryCompType::None:
				break;
				
			case EDZInventoryCompType::PlayerHotKey:
				ShouldPlaySound = IsItemCanAddToInventory_internal(ItemRuntimeData);
				break;
				
			case EDZInventoryCompType::PlayerBody:
				ShouldPlaySound= IsItemCanAddToBody_internal(ItemRuntimeData);
				break;
			}
		}
		
		// 게임 플레이 큐 요청
		if (!ShouldPlaySound) { K2_EndAbility(); return; }
		RequestAddGameplayCue(ItemRuntimeData.StaticDataID);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// END
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		K2_EndAbility();
	}
}

void UDZGA_PickUpItem::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#pragma endregion
//======================================================================================================================	
#pragma region 내부처리

	//━━━━━━━━━━━━━━━━━━━━
	// 내부처리
	//━━━━━━━━━━━━━━━━━━━━	

bool UDZGA_PickUpItem::AddItemToInventory_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck)
{
	if (!IsValid(TargetItem)) return false;

	// 플레이어 핫키 인벤토리 가져오기
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent = IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(HotKeyInventoryComponent)) return false; 

	// 아이템 넣기 시도 
	bool IsSuccess = IDZInventoryCompActionInterface::Execute_AddItemToInventory(HotKeyInventoryComponent, ItemRunTimeData);
	if (!IsSuccess) return false; 
					
	// 성공시 타겟 처리 
	TargetItem->Destroy();
	
	// 호스트 전용 (UI 알림 -> 클라는 OnRep에서 호출)
	BroadcastItemPickUp( HotKeyInventoryComponent->GetInventoryData().InventoryType, HotKeyInventoryComponent);
	return true;
}

bool UDZGA_PickUpItem::AddItemToBody_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck)
{
	if (!IsValid(TargetItem)) return false;
	
	// 플레이어 장비 인벤토리 가져오기
	UDZBodyEquipInventoryComponent* BodyEquipInventoryComponent = IPlayerCompGetterInterface::Execute_GetBodyEquipInventoryComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(BodyEquipInventoryComponent)) return false;
				
	// 아이템 넣기 시도 
	bool IsSuccess = IDZInventoryCompActionInterface::Execute_AddItemToInventory(BodyEquipInventoryComponent, ItemRunTimeData);
	if (!IsSuccess)  return false;
					
	// 성공시 타겟 처리 
	TargetItem->Destroy();

	// 잠기 비주얼 가져오기
	UDZBodyEquipVisualComponent* BodyEquipVisualComponent = IPlayerCompGetterInterface::Execute_GetBodyEquipVisualComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(BodyEquipVisualComponent)) return false;
	
	// 장비 비주얼 업데이트
	BodyEquipVisualComponent->HandleVisual(ItemStaticDataForCheck.ItemStaticInfo.MatchInventorySlotType);
	
	// 호스트 전용 (UI 알림 -> 클라는 OnRep에서 호출)
	BroadcastItemPickUp( BodyEquipInventoryComponent->GetInventoryData().InventoryType, BodyEquipInventoryComponent);
	return true;
}

bool UDZGA_PickUpItem::IsItemCanAddToInventory_internal(FDZItemRuntimeData& ItemRunTimeData)
{
	// 스택아이템인지 아닌지 판단 
	bool bIsStackItem = UTSItemCheckLibrary::IsThisITemCanStack_Lib(this,ItemRunTimeData);
	
	// 플레이어 핫키 인벤토리 가져오기
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent = IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(HotKeyInventoryComponent)){ K2_EndAbility(); return false; } 
	
	// 넣을 수 있는지 예측
	if (bIsStackItem)
	{
		int32 FoundSlotIndex = UDZInventoryInternalHelperLibrary::FindStackSlot_Lib(this, HotKeyInventoryComponent->GetInventoryData(), ItemRunTimeData);
		if (FoundSlotIndex >= 0) return true;
		
		int32 FoundSlot = UDZInventoryInternalHelperLibrary::FindEmptySlot_Lib(this, HotKeyInventoryComponent->GetInventoryData(), ItemRunTimeData);
		if (FoundSlot >= 0) return true;
	}
	else
	{
		int32 FoundSlot = UDZInventoryInternalHelperLibrary::FindEmptySlot_Lib(this, HotKeyInventoryComponent->GetInventoryData(), ItemRunTimeData);
		if (FoundSlot >= 0) return true;
	}
	
	return false;
}

bool UDZGA_PickUpItem::IsItemCanAddToBody_internal(FDZItemRuntimeData& ItemRunTimeData)
{
	// 스택아이템인지 아닌지 판단 
	bool bIsStackItem = UTSItemCheckLibrary::IsThisITemCanStack_Lib(this,ItemRunTimeData);
	
	// 플레이어 장비 인벤토리 가져오기
	UDZBodyEquipInventoryComponent* BodyEquipInventoryComponent = IPlayerCompGetterInterface::Execute_GetBodyEquipInventoryComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(BodyEquipInventoryComponent)){ K2_EndAbility(); return false; } 
	
	// 넣을 수 있는지 예측
	int32 FoundSlot = UDZInventoryInternalHelperLibrary::FindEmptySlot_Lib(this, BodyEquipInventoryComponent->GetInventoryData(), ItemRunTimeData);
	if (FoundSlot >= 0) return true;
	
	return false;
}

void UDZGA_PickUpItem::RequestAddGameplayCue(int32 ItemID)
{
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(ASC)) { K2_EndAbility(); return;}
	if (!ItemPickUpSoundGameplayCue.IsValid()) { K2_EndAbility(); return;}

	// 큐 파라미터 정보
	FGameplayCueParameters CueParams;
	CueParams.Instigator = GetAvatarActorFromActorInfo();
	CueParams.EffectCauser = GetAvatarActorFromActorInfo();
	CueParams.RawMagnitude = static_cast<float>(ItemID);// RawMagnitude 을 스태틱 ID 넘겨주는 것으로 쓰는 중!

	// 게임 플레이 큐 액터 스폰 요청
	ASC->ExecuteGameplayCue(ItemPickUpSoundGameplayCue, CueParams);
}

void UDZGA_PickUpItem::BroadcastItemPickUp(const EDZInventoryCompType InventoryCompType, UDZInventoryMasterComponent* InventoryComponentPtr) const
{
	if (!IsValid(InventoryComponentPtr)) return;
	if (InventoryCompType == EDZInventoryCompType::None) return;
	
	FDZInventoryUpdateMessage Message;
	Message.ChangeInventoryType = InventoryCompType;
	Message.InventoryComp = InventoryComponentPtr;
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.BroadcastMessage(DZ::Inventory::DZ_INVNETORY_UPDATE, Message);
}

#pragma endregion
//======================================================================================================================	