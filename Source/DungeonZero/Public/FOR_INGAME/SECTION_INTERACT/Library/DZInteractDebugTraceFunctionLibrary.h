// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZInteractDebugTraceFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInteractDebugTraceFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static	void DrawInteractionDebugLine_Lib(const UWorld* InWorld, const FVector& Start, const FVector& End, const FHitResult& HitResult, bool bHit);
	
};
