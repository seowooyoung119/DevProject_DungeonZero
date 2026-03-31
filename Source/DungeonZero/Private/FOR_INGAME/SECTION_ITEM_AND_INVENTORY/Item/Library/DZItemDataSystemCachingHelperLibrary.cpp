// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemDataSystemCachingHelperLibrary.h"

void UDZItemDataSystemCachingHelperLibrary::CacheItemDataTable_Lib(TObjectPtr<UDataTable> InTable, TMap<int32, FDZITemStaticData>& InOutMap)
{
	if (!IsValid(InTable))
	{
		UE_LOG(LogTemp, Warning, TEXT("InTable is not valid"));
		return;
	}
	
	TArray<FDZItemInfoTable*> Rows;
	InTable->GetAllRows<FDZItemInfoTable>(TEXT("ItemInfoLoad"), Rows);
	
	UE_LOG(LogTemp, Warning, TEXT("Rows Size: %d"), Rows.Num());
	
	for (FDZItemInfoTable* Row : Rows)
	{
		if (!Row)
		{
			UE_LOG(LogTemp, Warning, TEXT("Row is null"));
			continue;
		}
		if (Row->ItemID <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Row ID is invalid"));
			continue;
		}
		// 이미 등록된 ID인지 확인 (중복 방지)
		if (InOutMap.Contains(Row->ItemID))
		{
			UE_LOG(LogTemp, Warning, TEXT("Row ID is duplicated"));
			continue;
		}
		
		// 새로운 정적 데이터 구조체 생성 및 기본 정보 채우기
		FDZITemStaticData NewStaticData;
		NewStaticData.ItemStaticInfo = *Row;

		// 임시 맵에 추가
		InOutMap.Add(Row->ItemID, NewStaticData);
	}
}
