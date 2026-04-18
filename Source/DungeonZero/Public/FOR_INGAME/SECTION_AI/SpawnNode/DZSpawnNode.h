// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DZSpawnNode.generated.h"

UCLASS()
class DUNGEONZERO_API ADZSpawnNode : public AActor
{
	GENERATED_BODY()

public:
	ADZSpawnNode();
	
	FORCEINLINE	int32 GetSpawnAIClassID() const { return SpawnAIClassID; };

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | SpawnNode")
	int32 SpawnAIClassID = 0;
	
};
