// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZInteractDebugLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInteractDebugLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// 보고 있는 액터와 화면에 지난 액터 표시해주는 디버깅 함수
	UFUNCTION(BlueprintCallable, Category = "DZ | Debug")
	static void DebugInteractActors(const AActor* WorldContextObject, AActor* Current, AActor* Last);
	
};
