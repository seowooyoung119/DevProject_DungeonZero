// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Data/Table/DZAnomalySettingTable.h"
#include "FOR_INGAME/SECTION_STAGE/Data/Table/DZStageBalanceDataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StageBalanceDataLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UStageBalanceDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	// 스테이지 테이블 캐싱 함수
	static void CacheStageDataToMap(TMap<int32, FDZStageBalanceRow>& OutStageMap);

	// 스테이지 테이블 디버그 
	static void DebugLogStageMap(const TMap<int32, FDZStageBalanceRow>& InStageMap);
	
	// 어노말리 테이블 캐싱 함수 
	static void CacheAnomalyDataToMap(TMap<FName, FDZAnomalySettingTable>& OutStageMap);
	
	// 어노말리 테이블 로그 
	static void DebugLogAnomalyMap(const TMap<FName, FDZAnomalySettingTable>& InStageMap);
};
