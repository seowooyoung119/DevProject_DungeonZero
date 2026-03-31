// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_UseItem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_UseItem : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_UseItem();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
