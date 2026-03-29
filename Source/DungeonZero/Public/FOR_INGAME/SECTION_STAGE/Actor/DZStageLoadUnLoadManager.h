// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DZStageLoadUnLoadManager.generated.h"

UCLASS()
class DUNGEONZERO_API ADZStageLoadUnLoadManager : public AActor
{
	GENERATED_BODY()

public:
	ADZStageLoadUnLoadManager();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "DZ")
	void LoadStage(int32 InStageLevel);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "DZ")
	void UnLoadStage(int32 InStageLevel);

};
