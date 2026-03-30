// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DZInGameGM.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZInGameGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
};
