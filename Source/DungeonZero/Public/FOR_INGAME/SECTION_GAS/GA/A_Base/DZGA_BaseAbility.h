// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_BaseAbility.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_BaseAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Ability")
	bool bWantPrintDebug = false;
	
};
