// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/System/DZAIDataSystem.h"

#include "FOR_INGAME/SECTION_AI/Library/DZAIDataSystemCachingHelperLibrary.h"
#include "FOR_INGAME/SECTION_AI/Library/DZAIDataTableLogLibrary.h"
#include "FOR_INGAME/SECTION_AI/Setting/DZAISetting.h"


//======================================================================================================================	
#pragma region 게터
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	

UDZAIDataSystem* UDZAIDataSystem::Get(const UObject* InWorldContextObject)
{
	if (!IsValid(InWorldContextObject)) return nullptr;
	
	UWorld* World = InWorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
			
	UGameInstance* GameInstance = World->GetGameInstance();

	UDZAIDataSystem* AIDataSubSystem = GameInstance->GetSubsystem<UDZAIDataSystem>();
	if (!IsValid(AIDataSubSystem)) return nullptr;

	return AIDataSubSystem;
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
void UDZAIDataSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// 데이터 초기화
	AIDataMap.Empty();
	
	// 데이터 배열 공간 확보
	AIDataMap.Reserve(100);
	
	// 정적 데이터 테이블 캐싱 실시 
	InitializeItemStaticData_internal();
}

#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부 API
	//━━━━━━━━━━━━━━━━━━━━

FDZAIClassTable* UDZAIDataSystem::GetItemStaticData(int32 InItemID)
{
	if (!AIDataMap.Contains(InItemID)) return nullptr;
	return AIDataMap.Find(InItemID);
}

#pragma endregion
//======================================================================================================================	
#pragma region 내부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 내부 API
	//━━━━━━━━━━━━━━━━━━━━
	
void UDZAIDataSystem::InitializeItemStaticData_internal()
{
	// 1. DeveloperSettings에서 세팅 객체 가져오기
	const UDZAISetting* Settings = GetDefault<UDZAISetting>();
	if (!IsValid(Settings)) return;

	// [캐싱]
	UDZAIDataSystemCachingHelperLibrary::CacheAIDataTable_Lib(AIDataMap);
	
	UE_LOG(LogTemp, Warning, TEXT("AIDataMap Size: %d"), AIDataMap.Num());
	
	// 로그
	bWantPrintDeBugLog = Settings->bWantPrintDeBugLog;
	if (bWantPrintDeBugLog == false) return;
	for (const auto& [Key, Value] : AIDataMap)
	{
		UDZAIDataTableLogLibrary::LogAIData_Lib(&Value);
	}
}

#pragma endregion
//======================================================================================================================	