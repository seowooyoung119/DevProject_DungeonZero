// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyShadow.h"
#include "AbilitySystemComponent.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZGA_AnomalyShadow::UDZGA_AnomalyShadow()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
}

void UDZGA_AnomalyShadow::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// 현재 아무것도 안 하고 그냥 그림자로만 존재
}

void UDZGA_AnomalyShadow::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(ASC))
	{
		K2_EndAbility(); return;
	}
	if (!AnomalySealCueTag.IsValid())
	{
		K2_EndAbility(); return;
	}
	
	// 큐 파라미터 정보
	FGameplayCueParameters CueParams;
	CueParams.TargetAttachComponent = GetAvatarActorFromActorInfo()->GetRootComponent();
	CueParams.Instigator = GetAvatarActorFromActorInfo();
	CueParams.EffectCauser = GetAvatarActorFromActorInfo();
	CueParams.AbilityLevel = GetAbilityLevel();
	
	// 게임 플레이 큐 액터 스폰 요청
	ASC->AddGameplayCue(AnomalySealCueTag, CueParams);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#pragma endregion
//======================================================================================================================