// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Library/StageBalanceDataLibrary.h"

#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "FOR_INGAME/SECTION_STAGE/Setting/DZStageBalanceSetting.h"

void UStageBalanceDataLibrary::CacheStageDataToMap(TMap<int32, FDZStageBalanceRow>& OutStageMap)
{
	// 1. 세팅에서 데이터 테이블 포인터 가져오기
	const UDZStageBalanceSetting* Settings = GetDefault<UDZStageBalanceSetting>();
	if (!Settings || Settings->StageDataTable.IsNull()) return;

	// 2. 데이터 테이블 로드
	UDataTable* Table = Settings->StageDataTable.LoadSynchronous();
	if (!Table) return;

	// 3. 기존 맵 비우기 (중복 방지)
	OutStageMap.Empty();

	// 4. 모든 행 데이터 가져오기
	TArray<FDZStageBalanceRow*> AllRows;
	Table->GetAllRows<FDZStageBalanceRow>(TEXT("CacheStageData"), AllRows);

	// 5. TMap에 데이터 채우기 (Key: Level)
	for (const FDZStageBalanceRow* Row : AllRows)
	{
		if (Row) OutStageMap.Add(Row->Level, *Row);
	}
}

void UStageBalanceDataLibrary::DebugLogStageMap(const TMap<int32, FDZStageBalanceRow>& InStageMap)
{
	UE_LOG(LogTemp, Warning, TEXT("----------- [Stage Balance Map Debug Start] -----------"));
	UE_LOG(LogTemp, Warning, TEXT("Total Stages Cached: %d"), InStageMap.Num());

	for (const auto& Pair : InStageMap)
	{
		int32 LevelKey = Pair.Key;
		const FDZStageBalanceRow& Row = Pair.Value;

		// 한 줄에 모든 정보를 보기 쉽게 출력
		UE_LOG(LogTemp, Log, TEXT("[Level %d] -> Time: %.1fs | AnomalyCount: %d ~ %d"), 
			LevelKey, 
			Row.Time, 
			Row.MinAnomalyCount, 
			Row.MaxAnomalyCount);
	}

	UE_LOG(LogTemp, Warning, TEXT("----------- [Stage Balance Map Debug End] -------------"));
}

void UStageBalanceDataLibrary::CacheAnomalyDataToMap(TMap<FName, FDZAnomalySettingTable>& OutStageMap)
{
	// 1. 세팅에서 데이터 테이블 포인터 가져오기
	const UDZStageBalanceSetting* Settings = GetDefault<UDZStageBalanceSetting>();
	if (!Settings || Settings->StageDataTable.IsNull()) return;

	// 2. 데이터 테이블 로드
	UDataTable* Table = Settings->AnomalySettingTable.LoadSynchronous();
	if (!Table) return;

	// 3. 기존 맵 비우기 (중복 방지)
	OutStageMap.Empty();

	// 4. 데이터 테이블의 모든 RowMap을 가져와서 TMap에 복사
	// Table->GetRowMap()은 TMap<FName, uint8*>를 반환하므로 형변환
	for (auto It = Table->GetRowMap().CreateConstIterator(); It; ++It)
	{
		FName RowName = It.Key();
		FDZAnomalySettingTable* RowData = reinterpret_cast<FDZAnomalySettingTable*>(It.Value());

		if (RowData)
		{
			// RowName을 Key로 하여 맵에 추가
			OutStageMap.Add(RowName, *RowData);
		}
	}
}

void UStageBalanceDataLibrary::DebugLogAnomalyMap(const TMap<FName, FDZAnomalySettingTable>& InStageMap)
{
	UE_LOG(LogTemp, Warning, TEXT("================ [Anomaly Map Debug Start] ================"));
	UE_LOG(LogTemp, Warning, TEXT("Total Count: %d"), InStageMap.Num());

	for (const auto& Pair : InStageMap)
	{
		const FName& RowName = Pair.Key;
		const FDZAnomalySettingTable& Data = Pair.Value;

		// 클래스 이름 추출 (null 체크 포함)
		FString OriginalClassName = Data.AnomalyClass ? Data.AnomalyClass->GetName() : TEXT("NULL");
		FString AnomalyClassName = Data.AnomalyClass_Anomaly ? Data.AnomalyClass_Anomaly->GetName() : TEXT("NULL");

		UE_LOG(LogTemp, Log, TEXT("[%s] -> Original: %s | Anomaly: %s"), 
			*RowName.ToString(), 
			*OriginalClassName, 
			*AnomalyClassName);
	}

	UE_LOG(LogTemp, Warning, TEXT("================ [Anomaly Map Debug End] =================="));
}
