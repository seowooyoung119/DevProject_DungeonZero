// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/DataAsset/DZItemTablesDataAsset.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemDataSystemCachingHelperLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemDataTableLogLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Setting/DZItemDataSystemSettings.h"

//======================================================================================================================	
#pragma region 게터
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	

UDZItemDataSubSystem* UDZItemDataSubSystem::Get(const UObject* InWorldContextObject)
{
	if (!IsValid(InWorldContextObject)) return nullptr;
	
	UWorld* World = InWorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
			
	UGameInstance* GameInstance = World->GetGameInstance();

	UDZItemDataSubSystem* ItemDataSubSystem = GameInstance->GetSubsystem<UDZItemDataSubSystem>();
	if (!IsValid(ItemDataSubSystem)) return nullptr;

	return ItemDataSubSystem;
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
void UDZItemDataSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// 데이터 초기화
	ItemStaticDataArray.Empty();
	ItemStaticDataMap.Empty();
	
	// 데이터 배열 공간 확보
	ItemStaticDataArray.Reserve(100);
	ItemStaticDataMap.Reserve(100);
	
	// 정적 데이터 테이블 캐싱 실시 
	InitializeItemStaticData_internal();
}

#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부 API
	//━━━━━━━━━━━━━━━━━━━━

FDZITemStaticData* UDZItemDataSubSystem::GetItemStaticData(int32 InItemID)
{
	if (!ItemStaticDataMap.Contains(InItemID)) return nullptr;
	return *ItemStaticDataMap.Find(InItemID);
}

#pragma endregion
//======================================================================================================================	
#pragma region 내부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 내부 API
	//━━━━━━━━━━━━━━━━━━━━
	
void UDZItemDataSubSystem::InitializeItemStaticData_internal()
{
	// 1. DeveloperSettings에서 세팅 객체 가져오기
	const UDZItemDataSystemSettings* Settings = GetDefault<UDZItemDataSystemSettings>();
	if (!IsValid(Settings)) return;

	// 2. 소프트 포인터로 등록된 메인 데이터 에셋 로드하기
	UTSItemTablesDataAsset* MainDataAsset = Settings->GlobalItemDataAsset.LoadSynchronous();
	if (!IsValid(MainDataAsset)) return;

	// 테이이블 유효성 체크
	if (!IsValid(MainDataAsset->ItemInfoTable)) return;;

	// 캐싱용 임시 변수
	TMap<int32, FDZITemStaticData> TempItemStaticDataMap;
	TempItemStaticDataMap.Reserve(100);
	
	// [캐싱]
	UDZItemDataSystemCachingHelperLibrary::CacheItemDataTable_Lib(MainDataAsset->ItemInfoTable, TempItemStaticDataMap);
	
	UE_LOG(LogTemp, Warning, TEXT("TempItemStaticDataMap Size: %d"), TempItemStaticDataMap.Num());
	
	// 4. 배열에 데이터 넣기
	for (const auto& [Key, Value] : TempItemStaticDataMap)
	{
		ItemStaticDataArray.Add(Value);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("ItemStaticDataArray Size: %d"), ItemStaticDataArray.Num());
	
	// 5. 조회용 맵에 넣기.
	for (auto& StaticData : ItemStaticDataArray)
	{
		ItemStaticDataMap.Add(StaticData.ItemStaticInfo.ItemID, &StaticData);
	}
	
	// 로그
	bWantPrintDeBugLog = Settings->bWantPrintDeBugLog;
	if (bWantPrintDeBugLog == false) return;
	for (const auto& [Key, Value] : ItemStaticDataMap)
	{
		UTSItemDataTableLogLibrary::LogStaticItemData_Lib(Value);
	}
}

#pragma endregion
//======================================================================================================================	