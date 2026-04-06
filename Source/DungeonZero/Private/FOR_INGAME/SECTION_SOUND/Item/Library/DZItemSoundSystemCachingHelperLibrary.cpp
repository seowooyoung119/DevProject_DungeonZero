// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/Item/Library/DZItemSoundSystemCachingHelperLibrary.h"
#include "FOR_COMMON/SECTION_LOG/Item_And_Inventory/System/DZItemAndInventorySystemLOG.h"
#include "FOR_INGAME/SECTION_SOUND/Item/Data/Setting/DZItemSoundSystemSettings.h"

void UDZItemSoundSystemCachingHelperLibrary::CacheItemPickUpSoundDataTable_Lib(TMap<int32, FDZItemPickUpSoundTable>& InMap)
{
	// 1. DeveloperSettings에서 세팅 객체 가져오기
	const UDZItemSoundSystemSettings* Settings = GetDefault<UDZItemSoundSystemSettings>();
	if (!IsValid(Settings)) return;

	// 2. 소프트 포인터로 등록된 메인 데이터 에셋 로드하기
	UDataTable* Table = Settings->ItemPickSoundInfoTable.LoadSynchronous();
	if (!IsValid(Table)) return;
	
	TArray<FDZItemPickUpSoundTable*> Rows;
	Table->GetAllRows<FDZItemPickUpSoundTable>(TEXT("ItemInfoLoad"), Rows);
	
	UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Rows Size: %d"), Rows.Num());
	
	for (FDZItemPickUpSoundTable* Row : Rows)
	{
		if (!Row)
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Row is null"));
			continue;
		}
		if (Row->ItemID <= 0)
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Row ID is invalid"));
			continue;
		}
		
		// 이미 등록된 ID인지 확인 (중복 방지)
		if (InMap.Contains(Row->ItemID))
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Row ID is duplicated"));
			continue;
		}
		
		// 맵에 추가
		InMap.Add(Row->ItemID, *Row);
	}
	
}

void UDZItemSoundSystemCachingHelperLibrary::CacheItemDropSoundTable_Lib(TMap<int32, FDZItemDropSoundTable>& InMap)
{
	// 1. DeveloperSettings에서 세팅 객체 가져오기
	const UDZItemSoundSystemSettings* Settings = GetDefault<UDZItemSoundSystemSettings>();
	if (!IsValid(Settings)) return;

	// 2. 소프트 포인터로 등록된 메인 데이터 에셋 로드하기
	UDataTable* Table = Settings->ItemDropSoundInfoTable.LoadSynchronous();
	if (!IsValid(Table)) return;
	
	TArray<FDZItemDropSoundTable*> Rows;
	Table->GetAllRows<FDZItemDropSoundTable>(TEXT("ItemInfoLoad"), Rows);
	
	UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Rows Size: %d"), Rows.Num());
	
	for (FDZItemDropSoundTable* Row : Rows)
	{
		if (!Row)
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Row is null"));
			continue;
		}
		if (Row->ItemID <= 0)
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Row ID is invalid"));
			continue;
		}
		
		// 이미 등록된 ID인지 확인 (중복 방지)
		if (InMap.Contains(Row->ItemID))
		{
			UE_LOG(DZItemDataMgrLog, Warning, TEXT("ItemSoundData : Row ID is duplicated"));
			continue;
		}
		
		// 맵에 추가
		InMap.Add(Row->ItemID, *Row);
	}
}
