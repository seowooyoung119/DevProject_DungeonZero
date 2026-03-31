// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_PickUpItem : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_PickUpItem();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
