// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/Library/DZAIDataSystemCachingHelperLibrary.h"
#include "FOR_INGAME/SECTION_AI/Setting/DZAISetting.h"

void UDZAIDataSystemCachingHelperLibrary::CacheAIDataTable_Lib(TMap<int32, FDZAIClassTable>& Map)
{
	// 1. DeveloperSettings에서 세팅 객체 가져오기
	const UDZAISetting* Settings = GetDefault<UDZAISetting>();
	if (!IsValid(Settings)) return;

	// 2. 소프트 포인터로 등록된 메인 데이터 에셋 로드하기
	UDataTable* Table = Settings->AIInfoTable.LoadSynchronous();
	if (!IsValid(Table)) return;
	
	TArray<FDZAIClassTable*> Rows;
	Table->GetAllRows<FDZAIClassTable>(TEXT("ItemInfoLoad"), Rows);
	
	UE_LOG(LogTemp, Warning, TEXT("Rows Size: %d"), Rows.Num());
	
	for (FDZAIClassTable* Row : Rows)
	{
		if (!Row)
		{
			UE_LOG(LogTemp, Warning, TEXT("Row is null"));
			continue;
		}
		
		// 이미 등록된 ID인지 확인 (중복 방지)
		if (Map.Contains(Row->AIClassID))
		{
			UE_LOG(LogTemp, Warning, TEXT("Row ID is duplicated"));
			continue;
		}
		
		// AI 클래스 정보 확인
		if (!IsValid(Row->AIClass))
		{
			UE_LOG(LogTemp, Warning, TEXT("Row AI Class is invalid"));
			continue;
		}

		// 맵에 추가
		Map.Add(Row->AIClassID, *Row);
	}
}
