// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"


//======================================================================================================================	
#pragma region 라이프_사이클
	
	//──────────────
	// 라이프 사이클 
	//──────────────

ADZAnomalyActorBase::ADZAnomalyActorBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// rep
	bReplicates = true;
	SetReplicatingMovement(true);
}

// Called when the game starts or wen spawned
void ADZAnomalyActorBase::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion
//======================================================================================================================		
	