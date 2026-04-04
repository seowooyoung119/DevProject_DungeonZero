// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
UUDZStageRuntimePlayDataModule* UUDZStageRuntimePlayDataModule::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UUDZStageRuntimePlayDataModule* StageDataModule = World->GetSubsystem<UUDZStageRuntimePlayDataModule>();
	if (!IsValid(StageDataModule)) return nullptr;
	
	return StageDataModule;
}

#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━

bool UUDZStageRuntimePlayDataModule::HandleIsThereAnyAnomaly(AActor* InTargetActor)
{
	for (auto& AnomalyActor : AnomalyActors)
	{
		if (AnomalyActor == InTargetActor) return true;
	}
	
	return false;
}

#pragma endregion
//======================================================================================================================	