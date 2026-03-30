// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_FRAMEWORK/GameMode/DZInGameGM.h"
#include "FOR_INGAME/SECTION_STAGE/System/DZStageControlSystem.h"

void ADZInGameGM::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("InGameGM BeginPlay 에서 테스트하려고 StageControlSystem->StartGame() 호출하고 있음"));
		// 첫 스테이지 로드 요청
		UDZStageControlSystem* StageControlSystem = UDZStageControlSystem::Get(this);
		if (IsValid(StageControlSystem)) StageControlSystem->StartGame();
	}
}
