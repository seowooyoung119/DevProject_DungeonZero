// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FOR_INGAME/SECTION_SOUND/FootStep/Data/Struct/DZFootstepSoundData.h"
#include "DZFootStepSoundDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZFootStepSoundDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	// 표면별 사운드
	UPROPERTY(EditDefaultsOnly, Category = "DZ | Footstep")
	TMap<TEnumAsByte<EPhysicalSurface>, FDZFootstepSoundData> FootstepSounds;

	// Default 사운드
	UPROPERTY(EditDefaultsOnly, Category = "DZ | Footstep")
	FDZFootstepSoundData DefaultFootstepSound;
	
	// Default Attenuation
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundAttenuation> DefaultAttenuation = nullptr;
};
