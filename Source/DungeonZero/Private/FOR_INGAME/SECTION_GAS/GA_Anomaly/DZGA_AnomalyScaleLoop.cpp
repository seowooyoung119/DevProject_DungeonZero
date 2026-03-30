// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyScaleLoop.h"

//======================================================================================================================	
#pragma region 라이프_사이클

//──────────────
// 라이프 사이클 
//──────────────

UDZGA_AnomalyScaleLoop::UDZGA_AnomalyScaleLoop()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDZGA_AnomalyScaleLoop::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
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

	if (ScaleInterpolationDuration > 0.0f)
	{
		// 스케일 왕복 보간
		CachedAvatarActor = AvatarActor;
		ScaleInterpElapsedTime = 0.0f;

		if (!IsValid(GetWorld()))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
			return;
		}

		GetWorld()->GetTimerManager().SetTimer(
			ScaleInterpTimerHandle,
			this,
			&UDZGA_AnomalyScaleLoop::UpdateScaleInterp,
			ScaleInterpInterval,
			true);
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
}

void UDZGA_AnomalyScaleLoop::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsValid(GetWorld()) && ScaleInterpTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ScaleInterpTimerHandle);
	}

	CachedAvatarActor = nullptr;
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

//──────────────
// 어노말리 
//──────────────

void UDZGA_AnomalyScaleLoop::UpdateScaleInterp()
{
	AActor* AvatarActor = CachedAvatarActor.Get();
	if (!IsValid(AvatarActor))
	{
		const FGameplayAbilitySpecHandle Handle = GetCurrentAbilitySpecHandle();
		const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
		const FGameplayAbilityActivationInfo ActivationInfo = GetCurrentActivationInfo();
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	ScaleInterpElapsedTime += ScaleInterpInterval;
	float Alpha = 0.5f + 0.5f * FMath::Sin(2.0f * PI * ScaleInterpElapsedTime / ScaleInterpolationDuration - PI * 0.5f);
	float NewScale = FMath::Lerp(MinScale, MaxScale, Alpha);
	
	AvatarActor->SetActorScale3D(FVector(NewScale));
}
