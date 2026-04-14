// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_AnomalyJump.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_AnomalyJump : public UGameplayAbility
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZGA_AnomalyJump();
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
	UFUNCTION()
	void OnHitRelaunch(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    

	void Launch(const AActor* Instigator, const AActor* AvatarActor) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Anomaly | Jump")
	float ImpulseStrength = 1000.f;
	
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> CachedPrimitive = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> CachedInstigator;
#pragma endregion
//======================================================================================================================	
};
