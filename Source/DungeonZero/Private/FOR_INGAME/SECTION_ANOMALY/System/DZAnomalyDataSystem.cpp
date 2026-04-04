// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/System/DZAnomalyDataSystem.h"
#include "FOR_INGAME/SECTION_STAGE/Library/StageAllInOneHelpLibrary.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
UDZAnomalyDataSystem* UDZAnomalyDataSystem::Get(const UObject* InWorldContextObject)
{
	if (!IsValid(InWorldContextObject)) return nullptr;
	
	UWorld* World = InWorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
			
	UGameInstance* GameInstance = World->GetGameInstance();

	UDZAnomalyDataSystem* AnomalyDataSystem = GameInstance->GetSubsystem<UDZAnomalyDataSystem>();
	if (!IsValid(AnomalyDataSystem)) return nullptr;

	return AnomalyDataSystem;
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

void UDZAnomalyDataSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UStageAllInOneHelpLibrary::CacheAnomalyDataToMap(AnomalyDataMap);
	UStageAllInOneHelpLibrary::DebugLogAnomalyMap(AnomalyDataMap);
}

#pragma endregion	
//======================================================================================================================	
