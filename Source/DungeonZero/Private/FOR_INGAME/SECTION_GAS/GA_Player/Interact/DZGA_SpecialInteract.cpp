// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player/Interact/DZGA_SpecialInteract.h"

#include "FOR_COMMON/SECTION_TAG/GAS/Interact/DZInteractTag.h"
#include "FOR_INGAME/SECTION_INTERACT/Interface/DZCommonInteractInterface.h"

UDZGA_SpecialInteract::UDZGA_SpecialInteract()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Interact::DZ_INTERACT_SPECIALINTERACT);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Interact::DZ_INTERACT_SPECIALINTERACT);
	
	// 트리커 설정
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = DZ::Interact::DZ_INTERACT_SPECIALINTERACT;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;

	// 트리거 추가
	AbilityTriggers.Add(TriggerData);
}

void UDZGA_SpecialInteract::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
		const AActor* ConstTarget = Cast<AActor>(TriggerEventData->Target);
		if (!IsValid(ConstTarget)) { K2_EndAbility(); return; }
		AActor* ConstRemovedTarget = const_cast<AActor*>(ConstTarget);
		if (!IsValid(ConstRemovedTarget)) { K2_EndAbility(); return; }
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// 인터페이스 구현 확인 후 실행 요청
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		if (!ConstRemovedTarget->GetClass()->ImplementsInterface(UDZCommonInteractInterface::StaticClass()))  { K2_EndAbility(); return; } 
		FDZInteractData InteractData;
		InteractData.Instigator = GetAvatarActorFromActorInfo();
		IDZCommonInteractInterface::Execute_DoStandAloneInteractLogic(ConstRemovedTarget, InteractData);
		K2_EndAbility();
	}
}
