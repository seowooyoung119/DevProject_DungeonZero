// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZPlayerController : public APlayerController
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	ADZPlayerController();
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================	
	
	
};
