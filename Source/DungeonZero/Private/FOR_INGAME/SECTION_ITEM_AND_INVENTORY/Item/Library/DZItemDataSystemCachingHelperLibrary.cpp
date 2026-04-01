// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemDataSystemCachingHelperLibrary.h"
#include "FOR_COMMON/SECTION_LOG/Item_And_Inventory/System/DZItemAndInventorySystemLOG.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Setting/DZItemDataSystemSettings.h"

void UDZItemDataSystemCachingHelperLibrary::CacheItemDataTable_Lib(TMap<int32, FDZITemStaticData>& Map)
{
	// 1. DeveloperSettings에서 세팅 객체 가져오기
	const UDZItemDataSystemSettings* Settings = GetDefault<UDZItemDataSystemSettings>();
	if (!IsValid(Settings)) return;

	// 2. 소프트 포인터로 등록된 메인 데이터 에셋 로드하기
	UDataTable* Table = Settings->ItemInfoTable.LoadSynchronous();
	if (!IsValid(Table)) return;
	
	TArray<FDZItemInfoTable*> Rows;
	Table->GetAllRows<FDZItemInfoTable>(TEXT("ItemInfoLoad"), Rows);
	
	UE_LOG(DZItemDataMgrLog, Warning, TEXT("Rows Size: %d"), Rows.Num());
	
	for (FDZItemInfoTable* Row : Rows)
	{
		if (!Row)
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("Row is null"));
			continue;
		}
		if (Row->ItemID <= 0)
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("Row ID is invalid"));
			continue;
		}
		// 이미 등록된 ID인지 확인 (중복 방지)
		if (Map.Contains(Row->ItemID))
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("Row ID is duplicated"));
			continue;
		}
		
		// 새로운 정적 데이터 구조체 생성 및 기본 정보 채우기
		FDZITemStaticData NewStaticData;
		NewStaticData.ItemStaticInfo = *Row;

		// 맵에 추가
		Map.Add(Row->ItemID, NewStaticData);
	}
}
