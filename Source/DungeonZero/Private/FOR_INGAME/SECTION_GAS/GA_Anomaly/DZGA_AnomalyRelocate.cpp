// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyRelocate.h"

#include "NavigationSystem.h"

//======================================================================================================================	
#pragma region 라이프_사이클

//──────────────
// 라이프 사이클 
//──────────────

UDZGA_AnomalyRelocate::UDZGA_AnomalyRelocate()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDZGA_AnomalyRelocate::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

	ApplyRelocate(AvatarActor);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UDZGA_AnomalyRelocate::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo,
                                       bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

//──────────────
// 어노말리 
//──────────────

void UDZGA_AnomalyRelocate::ApplyRelocate(AActor* TargetActor)
{
	if (!IsValid(TargetActor))
	{
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!IsValid(NavSystem))
	{
		return;
	}

	const FVector OriginLocation = TargetActor->GetActorLocation();
	FVector ResultLocation = OriginLocation;
	
	// 맵 밖으로 나가지 않게 NavMesh 위로 투영
	FNavLocation ProjectedLocation;
	for (int32 i = 0; i < 30; i++)
	{
		float RandomAngle = FMath::FRandRange(0.f, 360.f);
		float RandomRadius = FMath::FRandRange(MinRelocateRadius, MaxRelocateRadius);
		FVector RandomOffset = FVector(RandomRadius * FMath::Cos(FMath::DegreesToRadians(RandomAngle)),
									   RandomRadius * FMath::Sin(FMath::DegreesToRadians(RandomAngle)), 
									   0.f);

		FVector TestLocation = OriginLocation + RandomOffset;
		FNavLocation NavLocation;
		if (NavSystem->ProjectPointToNavigation(TestLocation, NavLocation))
		{
			// NavMesh 위 값 저장
			ResultLocation = NavLocation.Location;
			break;
		}
	}
	
	TargetActor->SetActorLocation(ResultLocation);
}
