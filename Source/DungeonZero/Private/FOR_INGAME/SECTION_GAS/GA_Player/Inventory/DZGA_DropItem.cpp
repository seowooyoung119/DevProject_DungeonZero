// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player//Inventory/DZGA_DropItem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Invnetory/DZInventoryUpdateMSG.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/HotKey/DZHotKeyEquipVisualComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventorySlotInternalHelperLibrary.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZInventoryChannel.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZHotKeyTag.h"
#include "AbilitySystemComponent.h"

UDZGA_DropItem::UDZGA_DropItem()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Inventory::DZ_INVNETORY_DROP_ITEM);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Inventory::DZ_INVNETORY_DROP_ITEM);
}

void UDZGA_DropItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 필요 컴포넌트 체크 및 가져오기
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
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
	
	// 사운드 후 처리를 위한 정적 데이터 id 캐싱
	int32 ItemRuntimeDataID = InventoryCompData.InventoryDataArray[CurrentHotKeyIndex].ItemData.StaticDataID;
	
	// 실제 상호작용 로직 (서버에서만 실행)
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 아이템 버리기 실시 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
		// 핫키 인벤토리 드롭 실시 
		bool DropSuccess = IDZInventoryCompActionInterface::Execute_DropItemToFromInventory(HotKeyInventoryComponent, CurrentHotKeyIndex, 1);
		
		// 실패시 종료 (ga는 이미 실행되었지만 아이템 드롭에 실패해버림 좆됨. -> 되돌리는 게 불가능함. == 절대 실패해선 안 됨.)
		if (DropSuccess == false)
		{
			K2_EndAbility();
			return;
		}
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 핫키 비주얼 컴포넌트 후처리 
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		// 성공 시 후처리 이후 종료
		if (DropSuccess == true)
		{
			if (UDZInventorySlotInternalHelperLibrary::IsSlotEmpty_Lib(InventoryCompData.InventoryDataArray[CurrentHotKeyIndex]))
			{
				// 성공 시 비쥬얼 컴포넌트 체킹 (만약에 슬롯이 비었으면 지우기)
				HotKeyEquipVisualComponent->HideSpawnVisual();
				
				// 성공 시 핫키 인벤토리 컴포넌트 체킹 (만약에 슬롯이 비었으면 액티브 핫키 인덱스 되돌리기)
				HotKeyInventoryComponent->SetActiveHotKeyIndex(-1);
			}
			
			// 호스트 전용 (UI 알림 -> 클라는 OnRep에서 호출)
			FDZInventoryUpdateMessage Message;
			Message.ChangeInventoryType = HotKeyInventoryComponent->GetInventoryData().InventoryType;
			Message.InventoryComp = HotKeyInventoryComponent;
			UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
			MessageSubsystem.BroadcastMessage(DZ::Inventory::DZ_INVNETORY_UPDATE, Message);
		}
	}
			
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 후 처리 사운드 
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(ASC)) { K2_EndAbility(); return;}
	if (!ItemDropSoundGameplayCue.IsValid()) { K2_EndAbility(); return;}
	
	// 큐 파라미터 정보
	FGameplayCueParameters CueParams;
	CueParams.Instigator = GetAvatarActorFromActorInfo();
	CueParams.EffectCauser = GetAvatarActorFromActorInfo();
	CueParams.RawMagnitude = static_cast<float>(ItemRuntimeDataID);// RawMagnitude 을 스태틱 ID 넘겨주는 것으로 쓰는 중!
	
	// 게임 플레이 큐 액터 스폰 요청
	ASC->AddGameplayCue(ItemDropSoundGameplayCue, CueParams);
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// END
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	K2_EndAbility();
}
