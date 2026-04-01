// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZITemStaticData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZItemDataSystemCachingHelperLibrary.generated.h"

/**
 * 아이템 데이터 매니저가 초기 데이터 캐싱할 때 쓰는 라이브러리 
 */
UCLASS()
class DUNGEONZERO_API UDZItemDataSystemCachingHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// 아이템 데이터 시스템 캐싱 헬퍼 함수 
	static void CacheItemDataTable_Lib(TMap<int32, FDZITemStaticData>& Map);
};
