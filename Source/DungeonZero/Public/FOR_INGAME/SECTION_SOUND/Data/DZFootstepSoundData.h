// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZFootstepSoundData.generated.h"

USTRUCT(BlueprintType)
struct FDZFootstepSoundData
{
	GENERATED_BODY()

	// 왼발
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | FootstepSound")
	TObjectPtr<USoundBase> FootStep_Left = nullptr;
	// 오른발
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | FootstepSound")
	TObjectPtr<USoundBase> FootStep_Right = nullptr;
};
