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
	ItemStaticDataMap.Empty();
	
	// 데이터 배열 공간 확보
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
	return ItemStaticDataMap.Find(InItemID);
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

	// [캐싱]
	UDZItemDataSystemCachingHelperLibrary::CacheItemDataTable_Lib(ItemStaticDataMap);
	
	UE_LOG(LogTemp, Warning, TEXT("ItemStaticDataMap Size: %d"), ItemStaticDataMap.Num());
	
	// 로그
	bWantPrintDeBugLog = Settings->bWantPrintDeBugLog;
	if (bWantPrintDeBugLog == false) return;
	for (const auto& [Key, Value] : ItemStaticDataMap)
	{
		UTSItemDataTableLogLibrary::LogStaticItemData_Lib(&Value);
	}
}

#pragma endregion
//======================================================================================================================	