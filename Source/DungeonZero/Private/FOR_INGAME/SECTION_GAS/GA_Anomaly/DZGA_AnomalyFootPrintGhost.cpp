// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyFootPrintGhost.h"
#include "AbilitySystemComponent.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━

UDZGA_AnomalyFootPrintGhost::UDZGA_AnomalyFootPrintGhost()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDZGA_AnomalyFootPrintGhost::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (IsValid(ASC) && AnomalySealCueTag.IsValid())
	{
		// 큐 파라미터 정보
		FGameplayCueParameters CueParams;
		CueParams.TargetAttachComponent = GetAvatarActorFromActorInfo()->GetRootComponent();
		CueParams.Instigator = GetAvatarActorFromActorInfo();
		CueParams.EffectCauser = GetAvatarActorFromActorInfo();
		CueParams.AbilityLevel = GetAbilityLevel();
	
		// 게임 플레이 큐 요청
		ASC->AddGameplayCue(AnomalySealCueTag, CueParams);
	}
	
}

void UDZGA_AnomalyFootPrintGhost::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (IsValid(ASC) && AnomalySealCueTag.IsValid())
	{
		// 게임 플레이 큐 요청
		ASC->RemoveGameplayCue(AnomalySealCueTag);
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#pragma endregion
//======================================================================================================================