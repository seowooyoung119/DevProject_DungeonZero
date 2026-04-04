// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "DZGA_CharacterJump.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_CharacterJump : public UDZGA_BaseAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_CharacterJump();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
