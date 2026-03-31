// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA/Interact/DZGA_PickUpItem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Invnetory/DZInventoryUpdateMSG.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Interact/DZInteractTag.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZInventoryChannel.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Interface/DZItemInterface.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"
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
		UE_LOG(LogTemp, Warning, TEXT("PickUpItem Ability Activated"));
		UE_LOG(LogTemp, Warning, TEXT("PickUpItem Ability Target : %s"), *TriggerEventData->Target->GetName());
		
		// 캐스팅 후 const 제거
		const ADZItemActorBase* ConstTargetItem = CastChecked<ADZItemActorBase>(TriggerEventData->Target);
		if (!IsValid(ConstTargetItem)) { K2_EndAbility(); return; }
		ADZItemActorBase* TargetItem = const_cast<ADZItemActorBase*>(ConstTargetItem);
		if (!IsValid(TargetItem)) { K2_EndAbility(); return; }
		
		// 아이템 인터페이스 확인 
		IDZItemInterface* ItemInterface = CastChecked<IDZItemInterface>(TargetItem);
		if (!ItemInterface) { K2_EndAbility(); return; }
		
		// 아이템 데이터 가져오기 (레퍼런스)
		FDZItemRuntimeData& ItemRuntimeData = ItemInterface->GetItemRuntimeDataPtr();
		
		// 플레이어 인벤토리 가져오기
		if (!IsValid(GetAvatarActorFromActorInfo())) { K2_EndAbility(); return; } 
		UDZHotKeyInventoryComponent* HotKeyInventoryComponent = IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryCompo(GetAvatarActorFromActorInfo());
		if (!IsValid(HotKeyInventoryComponent)){ K2_EndAbility(); return; } 

		// 아이템 넣기 시도 
		bool IsSuccess = IDZInventoryCompActionInterface::Execute_AddItemToInventory(HotKeyInventoryComponent, ItemRuntimeData);
		if (IsSuccess)
		{
			UE_LOG(LogTemp, Warning, TEXT("PickUpItem Ability Success"));
			// 성공시 타겟 파괴
			TargetItem->Destroy();
			
			// 호스트 전용 (UI 알림 -> 클라는 OnRep에서 호출)
			FDZInventoryUpdateMessage Message;
			Message.ChangeInventoryType = HotKeyInventoryComponent->GetInventoryData().InventoryType;
			Message.InventoryComp = HotKeyInventoryComponent;
			UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
			MessageSubsystem.BroadcastMessage(DZ::Inventory::DZ_INVNETORY_UPDATE, Message);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PickUpItem Ability Failed"));
		}
		K2_EndAbility();
	}
}
