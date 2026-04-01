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
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================	

	
	
};
