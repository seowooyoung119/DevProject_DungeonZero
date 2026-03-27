// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZGetControllerLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGetControllerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static APlayerController* GetPlayerControllerFromComponent(AActor* InOwner); 
	

};
