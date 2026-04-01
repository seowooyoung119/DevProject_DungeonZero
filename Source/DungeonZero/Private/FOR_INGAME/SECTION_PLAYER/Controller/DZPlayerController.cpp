// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_PLAYER/Controller/DZPlayerController.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
ADZPlayerController::ADZPlayerController()
{
	// tick
	PrimaryActorTick.bCanEverTick = true;
}

void ADZPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// 입력 모드 설정
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	bShowMouseCursor = false;
}

#pragma endregion
//======================================================================================================================	
	