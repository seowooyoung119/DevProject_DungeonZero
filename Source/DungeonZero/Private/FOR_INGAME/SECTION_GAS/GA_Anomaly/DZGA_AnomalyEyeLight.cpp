// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyEyeLight.h"
#include "AbilitySystemComponent.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZGA_AnomalyEyeLight::UDZGA_AnomalyEyeLight()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDZGA_AnomalyEyeLight::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(ASC)) { K2_EndAbility(); return;}
	if (!AnomalyCueTag.IsValid()) { K2_EndAbility(); return;}
	
	// 큐 파라미터 정보
	FGameplayCueParameters CueParams;
	CueParams.TargetAttachComponent = GetAvatarActorFromActorInfo()->GetRootComponent();
	CueParams.Instigator = GetAvatarActorFromActorInfo();
	CueParams.EffectCauser = GetAvatarActorFromActorInfo();
	CueParams.AbilityLevel = GetAbilityLevel();
	
	// 게임 플레이 큐 액터 스폰 요청
	ASC->AddGameplayCue(AnomalyCueTag, CueParams);
}

void UDZGA_AnomalyEyeLight::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// ASC, 게임 플레이 큐 태그 체크
	if (UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo(); IsValid(ASC) && AnomalyCueTag.IsValid())
	{
		// 게임 플레이 큐 제거 요청
		ASC->RemoveGameplayCue(AnomalyCueTag);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#pragma endregion
//======================================================================================================================	