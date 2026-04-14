// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZLoopSoundCueData.generated.h"

USTRUCT(BlueprintType)
struct FDZLoopSoundCueData
{
	GENERATED_BODY()
	
	// 재생할 사운드
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | LoopSound")
	TObjectPtr<USoundBase> LoopSound = nullptr;
	// Attenuation
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | LoopSound")
	TObjectPtr<USoundAttenuation> Attenuation = nullptr;
};