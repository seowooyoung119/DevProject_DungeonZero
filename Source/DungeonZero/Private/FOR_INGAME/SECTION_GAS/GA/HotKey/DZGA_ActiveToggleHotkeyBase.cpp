// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA/HotKey/DZGA_ActiveToggleHotkeyBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/HotKey/DZHotKeyEquipVisualComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"

UDZGA_ActiveToggleHotkeyBase::UDZGA_ActiveToggleHotkeyBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	
	// 에셋 태그 (블루프린트에서 설정)
	// 부여 태그 (블루프린트에서 설정)
}

void UDZGA_ActiveToggleHotkeyBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!IsValid(GetAvatarActorFromActorInfo())) { K2_EndAbility(); return;}
	if (TargetHotKeyIndex == -1 ) { K2_EndAbility(); return;}
	
	UE_LOG(LogTemp, Warning, TEXT("TargetHotKeyIndex : %d"), TargetHotKeyIndex);
	
	// 현재 활성화 중인 핫키 인덱스 가져오기 
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryCompo(GetAvatarActorFromActorInfo());
	if (!IsValid(HotKeyInventoryComponent)) { K2_EndAbility(); return; }
	int32 CurrentHotKeyIndex = HotKeyInventoryComponent->GetActiveHotKeyIndex();
	
	UE_LOG(LogTemp, Warning, TEXT("CurrentHotKeyIndex : %d"), CurrentHotKeyIndex);
	
	// 핫키 비쥬얼 컴포넌트 가져오기 
	UDZHotKeyEquipVisualComponent* HotKeyEquipVisualComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyEquipVisualCompo(GetAvatarActorFromActorInfo());
	if (!IsValid(HotKeyEquipVisualComponent)) { K2_EndAbility(); return; }
	
	UE_LOG(LogTemp, Warning, TEXT("HotKeyEquipVisualComponent : %s"), *HotKeyEquipVisualComponent->GetName());
	
	// 핫키 인덱스가 -1인지 체크 : 만약에 -1인 경우 그냥 꺼내기 실행
	if (CurrentHotKeyIndex == -1)
	{
		HotKeyEquipVisualComponent->TrySpawnVisual(TargetHotKeyIndex);
		HotKeyInventoryComponent->SetActiveHotKeyIndex(TargetHotKeyIndex);
		K2_EndAbility(); 
		return;
	}
	
	// 핫키 인덱스가 같은지 체크 : 만약 같으면 꺼낸 거 회수 -> 핫키 인덱스 -1 만들어야 함.
	if (CurrentHotKeyIndex == TargetHotKeyIndex)
	{
		HotKeyEquipVisualComponent->HideSpawnVisual();
		HotKeyInventoryComponent->SetActiveHotKeyIndex(-1);
		K2_EndAbility(); 
		return;
	}
	
	// 다른 핫키 인덱스인지 체크 : 다른 경우 타겟 핫키로 인덱스를 수정하고 꺼내기 실행 (기존 꺼 부수고 실행)
	if (CurrentHotKeyIndex != TargetHotKeyIndex)
	{
		HotKeyEquipVisualComponent->SwapSpawnVisual(TargetHotKeyIndex);
		HotKeyInventoryComponent->SetActiveHotKeyIndex(TargetHotKeyIndex);
		K2_EndAbility(); return;
	}
	
	K2_EndAbility();
}
