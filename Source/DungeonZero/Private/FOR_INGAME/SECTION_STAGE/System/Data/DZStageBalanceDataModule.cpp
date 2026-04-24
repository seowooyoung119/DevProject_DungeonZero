// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Data/DZStageBalanceDataModule.h"
#include "FOR_INGAME/SECTION_STAGE/Library/StageAllInOneHelpLibrary.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
UDZStageBalanceDataModule* UDZStageBalanceDataModule::Get(const UObject* InWorldContextObject)
{
	if (!IsValid(InWorldContextObject)) return nullptr;
	
	UWorld* World = InWorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
			
	UGameInstance* GameInstance = World->GetGameInstance();

	UDZStageBalanceDataModule* StageBalanceDataModule = GameInstance->GetSubsystem<UDZStageBalanceDataModule>();
	if (!IsValid(StageBalanceDataModule)) return nullptr;

	return StageBalanceDataModule;
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

void UDZStageBalanceDataModule::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// 필요 데이터 캐싱 실시 
	UStageAllInOneHelpLibrary::CacheStageDataToMap(StageDataMap);
	UStageAllInOneHelpLibrary::DebugLogStageMap(StageDataMap);
}

#pragma endregion	
//======================================================================================================================	