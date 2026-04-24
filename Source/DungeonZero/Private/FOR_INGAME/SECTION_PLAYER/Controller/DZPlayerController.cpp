// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_PLAYER/Controller/DZPlayerController.h"

//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━

#pragma endregion
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
	
	// 카메라 페이드
	if (IsValid(PlayerCameraManager)) PlayerCameraManager->StartCameraFade(1.f, 0.f, 10.f, FLinearColor::Black, 
		true, true);
	
	// 입력 모드 설정
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	bShowMouseCursor = false;
	
}

#pragma endregion
//======================================================================================================================	
