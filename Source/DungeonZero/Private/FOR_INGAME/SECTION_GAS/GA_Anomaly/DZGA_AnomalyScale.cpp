// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyScale.h"

#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"


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

void UDZGA_AnomalyScale::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
	// 최소 변화량 보장
	const bool bCanShrink = MinScale <= 1.f - MinScaleDelta;
	const bool bCanGrow = MaxScale >= 1.f + MinScaleDelta;
	float NewScale = 1.f;
	if (bCanShrink && bCanGrow)
	{
		NewScale = FMath::RandBool()
			           ? FMath::RandRange(MinScale, 1.f - MinScaleDelta)
			           : FMath::RandRange(1.f + MinScaleDelta, MaxScale);
	}
	else if (bCanShrink)
	{
		NewScale = FMath::RandRange(MinScale, 1.f - MinScaleDelta);
	}
	else if (bCanGrow)
	{
		NewScale = FMath::RandRange(1.f + MinScaleDelta, MaxScale);
	}
	else
	{
		// 크기 변화 범위 오류 로그 출력
		UE_LOG(LogTemp, Warning, TEXT("UDZGA_AnomalyScale::ActivateAbility() : %s No valid scale range!"), *AvatarActor->GetName());
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	ApplyScale(AvatarActor, NewScale);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UDZGA_AnomalyScale::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
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

	if (ADZAnomalyActorBase* AnomalyActor = Cast<ADZAnomalyActorBase>(TargetActor))
	{
		AnomalyActor->SetAnomalyScale(NewScale);
	}
}

#pragma endregion
//======================================================================================================================	
