// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "DZGA_SpecialInteract.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_SpecialInteract : public UDZGA_BaseAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_SpecialInteract();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
