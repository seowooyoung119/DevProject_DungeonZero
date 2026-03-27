// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DZAnomalyActorBase.generated.h"

UCLASS()
class DUNGEONZERO_API ADZAnomalyActorBase : public AActor
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//──────────────
	// 라이프 사이클 
	//──────────────
	
public:
	ADZAnomalyActorBase();
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================		
	
};
