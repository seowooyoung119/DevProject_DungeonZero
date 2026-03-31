// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_AnomalyPatrol.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_AnomalyPatrol : public UGameplayAbility
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZGA_AnomalyPatrol();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
								 const FGameplayAbilityActivationInfo ActivationInfo,
								 const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;
#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리
	//━━━━━━━━━━━━━━━━━━━━	
protected:
	// 패트롤 범위
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Patrol")
	float MinPatrolRadius = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Patrol")
	float MaxPatrolRadius = 300.f;
	// 이동 속도
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Patrol")
	float PatrolSpeed = 100.f;
	// 이동 쿨타임
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Patrol")
	float PatrolIdleDuration = 10.f;

private:
	
	FTimerHandle PatrolPhaseTimerHandle;
	FTimerHandle PatrolMoveTickTimerHandle;

	FVector PatrolStartLocation = FVector::ZeroVector;
	FVector PatrolDestination = FVector::ZeroVector;
	float PatrolMoveStartTime = 0.0f;
	float PatrolMoveDuration = 0.0f;
	
	static constexpr float PatrolTick = 0.016f;
	
	FVector GetPatrolLocation(AActor* TargetActor);
	void StartIdlePhase(AActor* TargetActor);
	void StartMovePhase(AActor* TargetActor);
	void PatrolMoveTick(AActor* TargetActor);
#pragma endregion
//======================================================================================================================	
};
