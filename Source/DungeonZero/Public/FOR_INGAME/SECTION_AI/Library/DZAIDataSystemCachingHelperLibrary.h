// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_AI/Data/Table/DZAIClassTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZAIDataSystemCachingHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAIDataSystemCachingHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// AI 데이터 시스템 캐싱 헬퍼 함수 
	static void CacheAIDataTable_Lib(TMap<int32, FDZAIClassTable>& Map);
};
