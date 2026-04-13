// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DZAnomalyMotionInterface.generated.h"

UINTERFACE()
class UDZAnomalyMotionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZAnomalyMotionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Motion")
	void StartAnomalyMotion();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Motion")
	void StopAnomalyMotion();
};
