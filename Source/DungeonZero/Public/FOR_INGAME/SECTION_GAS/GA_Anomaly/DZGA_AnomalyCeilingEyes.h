// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_AnomalyCeilingEyes.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_AnomalyCeilingEyes : public UGameplayAbility
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	
	UDZGA_AnomalyCeilingEyes();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

#pragma endregion
//======================================================================================================================	
#pragma region 어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리
	//━━━━━━━━━━━━━━━━━━━━	
private:
	
	// 어노말리 발각 후 양피지에 의해 봉인될 때 발생시킬 게임플레이 큐 태그
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FGameplayTag AnomalySealCueTag = FGameplayTag::EmptyTag;

#pragma endregion
//======================================================================================================================		
};
