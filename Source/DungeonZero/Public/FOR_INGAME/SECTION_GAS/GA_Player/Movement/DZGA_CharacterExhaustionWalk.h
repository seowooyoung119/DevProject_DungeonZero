// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "DZGA_CharacterExhaustionWalk.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_CharacterExhaustionWalk : public UDZGA_BaseAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_CharacterExhaustionWalk();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	UFUNCTION()
	void DelayForRegain();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDZGA_CharacterExhaustionWalk")
	float DelayTime = 3.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDZGA_CharacterExhaustionWalk")
	float ExhaustionWalkSpeed = 50.0f;
	
	UPROPERTY()
	float OriginalWalkSpeed = 0.0f;

};
