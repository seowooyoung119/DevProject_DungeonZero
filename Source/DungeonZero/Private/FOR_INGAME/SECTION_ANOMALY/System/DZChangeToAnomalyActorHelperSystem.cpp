// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/System/DZChangeToAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/Library/StageBalanceDataLibrary.h"

//======================================================================================================================	
#pragma region Getter	
UDZChangeToAnomalyActorHelperSystem* UDZChangeToAnomalyActorHelperSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZChangeToAnomalyActorHelperSystem* ChangeToAnomalyActorHelperSystem = World->GetSubsystem<UDZChangeToAnomalyActorHelperSystem>();
	if (!IsValid(ChangeToAnomalyActorHelperSystem)) return nullptr;
	
	return ChangeToAnomalyActorHelperSystem;
}
#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle
void UDZChangeToAnomalyActorHelperSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UStageBalanceDataLibrary::CacheAnomalyDataToMap(AnomalyDataMap);
	UStageBalanceDataLibrary::DebugLogAnomalyMap(AnomalyDataMap);
}

#pragma endregion
//======================================================================================================================	
#pragma region StageAPI
TArray<AActor*> UDZChangeToAnomalyActorHelperSystem::ReplaceWithAnomalyActors_internal(const TArray<AActor*>& SelectedActors)
{
	return TArray<AActor*>();
}

#pragma endregion
//======================================================================================================================	