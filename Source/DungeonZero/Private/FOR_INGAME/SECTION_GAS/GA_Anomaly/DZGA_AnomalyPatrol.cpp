// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyPatrol.h"

#include "NavigationSystem.h"
//======================================================================================================================	
#pragma region 라이프_사이클

//──────────────
// 라이프 사이클 
//──────────────
UDZGA_AnomalyPatrol::UDZGA_AnomalyPatrol()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDZGA_AnomalyPatrol::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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

	StartIdlePhase(AvatarActor);
}

void UDZGA_AnomalyPatrol::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().ClearTimer(PatrolPhaseTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(PatrolMoveTickTimerHandle);
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

//──────────────
// 어노말리 
//──────────────

FVector UDZGA_AnomalyPatrol::GetPatrolLocation(AActor* TargetActor)
{
	if (!IsValid(TargetActor))
	{
		return FVector::ZeroVector;
	}

	const FVector OriginLocation = TargetActor->GetActorLocation();
	FVector ResultLocation = OriginLocation;
	// 피벗 ~ 바닥 거리 계산 
	// 바운딩 박스 기준: 피벗이 바닥 중심이 아닌 액터에 대응
	const FBox   ActorBox      = TargetActor->GetComponentsBoundingBox();
	const float  PivotToBottom = OriginLocation.Z - ActorBox.Min.Z;
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!IsValid(NavSystem))
	{
		return ResultLocation;
	}
	bool bFound = false;
	// 맵 밖으로 나가지 않게 NavMesh 위로 투영
	FNavLocation ProjectedLocation;
	for (int32 i = 0; i < 30; i++)
	{
		float RandomAngle = FMath::FRandRange(0.f, 360.f);
		float RandomRadius = FMath::FRandRange(MinPatrolRadius, MaxPatrolRadius);
		FVector RandomOffset = FVector(RandomRadius * FMath::Cos(FMath::DegreesToRadians(RandomAngle)),
		                               RandomRadius * FMath::Sin(FMath::DegreesToRadians(RandomAngle)),
		                               0.f);

		FVector TestLocation = OriginLocation + RandomOffset;
		FNavLocation NavLocation;
		if (NavSystem->ProjectPointToNavigation(TestLocation, NavLocation))
		{
			// NavMesh 위 값 저장
			ResultLocation = NavLocation.Location;
			bFound = true;
			break;
		}
	}
	// 위치 탐색 실패 시 원 위치 반환
	if (!bFound)
	{
		return OriginLocation;
	}
	ResultLocation.Z += PivotToBottom;
	return ResultLocation;
}

void UDZGA_AnomalyPatrol::StartIdlePhase(AActor* TargetActor)
{
	// 이동 틱 정리
	GetWorld()->GetTimerManager().ClearTimer(PatrolMoveTickTimerHandle);
	// PatrolIdleDuration 이후 이동 페이즈 타이머 시작
	GetWorld()->GetTimerManager().SetTimer(
		PatrolPhaseTimerHandle,
		[this, TargetActor]() { StartMovePhase(TargetActor); },
		PatrolIdleDuration,
		false
	);
}

void UDZGA_AnomalyPatrol::StartMovePhase(AActor* TargetActor)
{
	PatrolStartLocation = TargetActor->GetActorLocation();
	PatrolDestination = GetPatrolLocation(TargetActor);
	const float Dist = FVector::Dist(PatrolStartLocation, PatrolDestination);
	// 목적지를 찾지 못하면 Idle 페이즈 시작
	if (Dist < KINDA_SMALL_NUMBER)
	{
		StartIdlePhase(TargetActor);
		return;
	}
	PatrolMoveDuration = Dist / PatrolSpeed;
	PatrolMoveStartTime = GetWorld()->GetTimeSeconds();

	// 이동 후 Idle 페이즈 타이머 시작
	GetWorld()->GetTimerManager().SetTimer(
		PatrolPhaseTimerHandle,
		[this, TargetActor]() { StartIdlePhase(TargetActor); },
		PatrolMoveDuration,
		false
	);
	// 이동 틱 타이머 시작
	GetWorld()->GetTimerManager().SetTimer(
		PatrolMoveTickTimerHandle,
		[this, TargetActor]() { PatrolMoveTick(TargetActor); },
		PatrolTick,
		true
	);
}

void UDZGA_AnomalyPatrol::PatrolMoveTick(AActor* TargetActor)
{
	if (!IsValid(TargetActor))
	{
		return;
	}
	float ElapsedTime = GetWorld()->GetTimeSeconds() - PatrolMoveStartTime;
	float Alpha = FMath::Clamp(ElapsedTime / PatrolMoveDuration, 0.f, 1.f);
	TargetActor->SetActorLocation(FMath::Lerp(PatrolStartLocation, PatrolDestination, Alpha));
}

#pragma endregion
//======================================================================================================================	
