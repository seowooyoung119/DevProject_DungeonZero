// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/OriginActor/Base/DZOriginActorBase.h"

#include "FOR_INGAME/SECTION_ANOMALY/System/DZRegisterAllCanBeAnomalyActorHelperSystem.h"

//======================================================================================================================	
#pragma region 라이프_사이클

//──────────────
// 라이프 사이클 
//──────────────

ADZOriginActorBase::ADZOriginActorBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;

	// rep
	bReplicates = true;
}

void ADZOriginActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Origin액터 등록
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem =
		UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(this);
	if (IsValid(RegisterAllCanBeAnomalyActorHelperSystem))
	{
		RegisterAllCanBeAnomalyActorHelperSystem->RegisterAllCanBeAnomalyActor(this);
	}
}
#pragma endregion
//======================================================================================================================	
