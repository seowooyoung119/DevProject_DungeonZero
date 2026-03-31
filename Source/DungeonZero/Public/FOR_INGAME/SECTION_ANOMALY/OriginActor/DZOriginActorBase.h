// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DZOriginActorBase.generated.h"

UCLASS()
class DUNGEONZERO_API ADZOriginActorBase : public AActor
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

public:
	ADZOriginActorBase();

protected:
	virtual void BeginPlay() override;

#pragma endregion
//======================================================================================================================	
};
