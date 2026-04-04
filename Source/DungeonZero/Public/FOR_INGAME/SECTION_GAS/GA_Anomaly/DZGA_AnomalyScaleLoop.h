// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_AnomalyScaleLoop.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_AnomalyScaleLoop : public UGameplayAbility
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZGA_AnomalyScaleLoop();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리
	//━━━━━━━━━━━━━━━━━━━━	
public:
	// 크기 변환 범위
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | ScaleLoop")
	float MinScale = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | ScaleLoop")
	float MaxScale = 5.0f;
	// 크기 변환 주기
	// 0 이하 즉시 변환
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | ScaleLoop")
	float ScaleInterpolationDuration = 0.0f;

protected:
	void UpdateScaleInterp();
	
	UPROPERTY()
	TWeakObjectPtr<AActor> CachedAvatarActor = nullptr;
	
	FTimerHandle ScaleInterpTimerHandle;
	float ScaleInterpElapsedTime = 0.0f;
	static constexpr float ScaleInterpInterval = 0.03f;
	
#pragma endregion
//======================================================================================================================	

};
