// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player/RightClick/DZGA_UseItem.h"
#include "FOR_COMMON/SECTION_TAG/GAS/RightClick/DZRightClickTag.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/HotKey/DZHotKeyEquipVisualComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventorySlotInternalHelperLibrary.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Invnetory/DZInventoryUpdateMSG.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"
#include "FOR_INGAME/SECTION_INTERACT/Comp/DZInteractComponent.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZInventoryChannel.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "AbilitySystemComponent.h"
#include "FOR_COMMON/SECTION_LOG/GA/PlayerGALOG.h"

UDZGA_UseItem::UDZGA_UseItem()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::RightClick::DZ_RIGHTCLICK_USEITEM);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::RightClick::DZ_RIGHTCLICK_USEITEM);
	
	// 트리커 설정
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = DZ::RightClick::DZ_RIGHTCLICK_USEITEM;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;

	// 트리거 추가
	AbilityTriggers.Add(TriggerData);
}

void UDZGA_UseItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!TriggerEventData) { K2_EndAbility(); return; }
	
	// 실제 상호작용 로직 (서버에서만 실행)
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		UE_LOG(DZPlayerGA_USeItem, Warning, TEXT("UseItem Ability Activated"));

		// NOTE //
		// 컨트롤러 중시으로 회전하면 서버에서 인터렉트 컴포넌트 디버그 라인으로 테스트 시 로컬에서 플레이어가 보는 것과 같은 액터를 집고 있음 //
		// 따라서 타겟을 다시 체크할 필요 없고, 서버의 인터렉트 컴포넌트에서 바로 현재 보고 있는 액터를 가져오면 되므로 여기서는 관련된 로직을 실행하지 않음)

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 필요 컴포넌트 체크 및 가져오기
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		// 인터렉트 컴포넌트 체크
		UDZInteractComponent* InteractComponent = IPlayerCompGetterInterface::Execute_GetDZInteractComponent(GetAvatarActorFromActorInfo());
		if (!IsValid(InteractComponent)) { K2_EndAbility(); return;}; 
		
		// 현재 활성화 중인 핫키 인벤토리 컴포넌트 가져오기 
		UDZHotKeyInventoryComponent* HotKeyInventoryComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryComponent(GetAvatarActorFromActorInfo());
		if (!IsValid(HotKeyInventoryComponent)) { K2_EndAbility(); return; }
	
		// 핫키 비쥬얼 컴포넌트 가져오기 
		UDZHotKeyEquipVisualComponent* HotKeyEquipVisualComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyEquipVisualComponent(GetAvatarActorFromActorInfo());
		if (!IsValid(HotKeyEquipVisualComponent)) { K2_EndAbility(); return; }

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 활성화 중인 핫키 체크
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		// 현재 활성화 중인 핫키 인덱스 가져오기 
		int32 CurrentHotKeyIndex = HotKeyInventoryComponent->GetActiveHotKeyIndex();
	
		// 슬롯 유효 체크
		FDZInventoryCompData& InventoryCompData = HotKeyInventoryComponent->GetInventoryData();
		if (!InventoryCompData.InventoryDataArray.IsValidIndex(CurrentHotKeyIndex)) { K2_EndAbility(); return; }
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 활성화해야 하는 아이템 어빌리티 가져오기 및 실행
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		// 정적 데이터 가져오기 
		UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
		if (!IsValid(ItemDataSubSystem))  { K2_EndAbility(); return; }
		FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(InventoryCompData.InventoryDataArray[CurrentHotKeyIndex].ItemData.StaticDataID);
		if (!ItemStaticData) { K2_EndAbility(); return; }
	
		// 아이템 어빌리티 체크 
		if (!IsValid(ItemStaticData->ItemStaticInfo.ItemGA)) { K2_EndAbility(); return;}
	
		// AbilitySpec 생성
		FGameplayAbilitySpec Spec(ItemStaticData->ItemStaticInfo.ItemGA, 1);

		// 어빌리티 부여 및 즉시 실행
		FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySystemComponentFromActorInfo()->GiveAbilityAndActivateOnce(Spec);
		if (!AbilitySpecHandle.IsValid()) { K2_EndAbility(); return; }
	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 핫키 비주얼 컴포넌트, 인벤토리 후처리 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		// 핸들이 유효하면 아이템 제거 실시 
		bool DeleteSuccess = IDZInventoryCompActionInterface::Execute_RemoveItemFromInventory(HotKeyInventoryComponent, CurrentHotKeyIndex, 1);
		
		// 실패시 종료 (ga는 이미 실행되었지만 아이템 제거에 실패해버림 좆됨. -> 되돌리는 게 불가능함. == 절대 실패해선 안 됨.)
		if (DeleteSuccess == false)
		{
			UE_LOG(DZPlayerGA_USeItem, Warning, TEXT("UseItem Fail"));
			K2_EndAbility();
			return;
		}
		
		// 성공 시 후처리 이후 종료
		if (DeleteSuccess == true)
		{
			// 성공 시 비쥬얼 컴포넌트 체킹 (만약에 슬롯이 비었으면 지우기)
			if (UDZInventorySlotInternalHelperLibrary::IsSlotEmpty_Lib(InventoryCompData.InventoryDataArray[CurrentHotKeyIndex]))
			{
				HotKeyEquipVisualComponent->HideSpawnVisual();
			}
			
			// 호스트 전용 (UI 알림 -> 클라는 OnRep에서 호출)
			FDZInventoryUpdateMessage Message;
			Message.ChangeInventoryType = HotKeyInventoryComponent->GetInventoryData().InventoryType;
			Message.InventoryComp = HotKeyInventoryComponent;
			UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
			MessageSubsystem.BroadcastMessage(DZ::Inventory::DZ_INVNETORY_UPDATE, Message);
			
			UE_LOG(DZPlayerGA_USeItem, Warning, TEXT("UseItem Success"));
			UE_LOG(DZPlayerGA_USeItem, Warning, TEXT("ItemGA Name %s"), *ItemStaticData->ItemStaticInfo.ItemGA->GetName());
			K2_EndAbility();
			return;
		}
	}
}
