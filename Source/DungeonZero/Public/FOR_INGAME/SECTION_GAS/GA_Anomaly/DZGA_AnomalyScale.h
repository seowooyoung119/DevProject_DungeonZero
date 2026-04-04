// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_AnomalyScale.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_AnomalyScale : public UGameplayAbility
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZGA_AnomalyScale();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리
	//━━━━━━━━━━━━━━━━━━━━	
public:
	// 크기 변환 최소값 (1.0 - MinScaleDelta 이하여야 함)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Scale")
	float MinScale = 0.5f;
	// 크기 변환 최대값 (1.0 + MinScaleDelta 이상이어야 함)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Scale")
	float MaxScale = 5.0f;
	// 크기 최소 변화량
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Scale")
	float MinScaleDelta = 0.3f;

protected:
	void ApplyScale(AActor* TargetActor, float NewScale);

#pragma endregion
//======================================================================================================================	

};
