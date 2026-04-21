// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DZFakeAnomalyHandleManager.generated.h"

UCLASS()
class DUNGEONZERO_API ADZFakeAnomalyHandleManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADZFakeAnomalyHandleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
