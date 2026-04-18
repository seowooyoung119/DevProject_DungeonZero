// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UpdateSenseLibrary.generated.h"

class UAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UUpdateSenseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	/** AI의 청각 감지 거리를 실시간으로 수정합니다. */
	UFUNCTION(BlueprintCallable, Category = "DZ | AI")
	static void UpdateHearingRange(UAIPerceptionComponent* PerceptionComponent, float NewRange, float LoseHearRadius);

	/** AI의 시야 감지 거리를 실시간으로 수정합니다. */
	UFUNCTION(BlueprintCallable, Category = "DZ | AI")
	static void UpdateSightRange(UAIPerceptionComponent* PerceptionComponent, float NewRange, float LoseSightRadius);
};
