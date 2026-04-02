// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZGetControllerLibrary.generated.h"

/**
 * 컨트롤러 게터 헬퍼 라이브러리 
 */
UCLASS()
class DUNGEONZERO_API UDZGetControllerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static APlayerController* GetPlayerControllerFromComponent(AActor* InOwner); 
	static APlayerController* GetPlayerControllerFromActor(AActor* InOwner);

};
