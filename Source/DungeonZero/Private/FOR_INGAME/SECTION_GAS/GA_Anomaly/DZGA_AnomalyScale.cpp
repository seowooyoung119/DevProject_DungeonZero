// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyScale.h"


//======================================================================================================================	
#pragma region 라이프_사이클

//──────────────
// 라이프 사이클 
//──────────────

UDZGA_AnomalyScale::UDZGA_AnomalyScale()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDZGA_AnomalyScale::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo,
                                         const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!IsValid(AvatarActor))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 랜덤 스케일 변환
	float NewScale = FMath::FRandRange(MinScale, MaxScale);
	ApplyScale(AvatarActor, NewScale);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UDZGA_AnomalyScale::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                    bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

//──────────────
// 어노말리 
//──────────────
void UDZGA_AnomalyScale::ApplyScale(AActor* TargetActor, float NewScale)
{
	if (!IsValid(TargetActor))
	{
		return;
	}
	TargetActor->SetActorScale3D(FVector(NewScale));
}

#pragma endregion
//======================================================================================================================	
