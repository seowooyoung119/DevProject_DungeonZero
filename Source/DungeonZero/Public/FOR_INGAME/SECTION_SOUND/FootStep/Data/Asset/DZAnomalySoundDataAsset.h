// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DZAnomalySoundDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAnomalySoundDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	
	// 표면별 사운드
	UPROPERTY(EditDefaultsOnly, Category = "DZ | AnomalySound")
	TMap<TEnumAsByte<EPhysicalSurface>, TObjectPtr<USoundBase>> AnomalySounds;
	
	// DefaultSound
	UPROPERTY(EditDefaultsOnly, Category = "DZ | AnomalySound")
	TObjectPtr<USoundBase> DefaultSound = nullptr;
	
	// Default Attenuation
	UPROPERTY(EditDefaultsOnly, Category = "DZ | AnomalySound")
	TObjectPtr<USoundAttenuation> DefaultAttenuation = nullptr;
	
	// Default Concurrency
	UPROPERTY(EditDefaultsOnly, Category = "DZ | AnomalySound")
	TObjectPtr<USoundConcurrency> DefaultConcurrency = nullptr;
};
