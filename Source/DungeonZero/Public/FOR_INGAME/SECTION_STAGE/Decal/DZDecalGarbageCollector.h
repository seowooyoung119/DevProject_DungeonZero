// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DZDecalGarbageCollector.generated.h"

UCLASS()
class DUNGEONZERO_API ADZDecalGarbageCollector : public AActor
{
	GENERATED_BODY()

public:
	ADZDecalGarbageCollector();
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void GCAllDecals();
	
};
