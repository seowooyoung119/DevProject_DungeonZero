// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZITemStaticData.h"
#include "DZItemDataTableLogLibrary.generated.h"


/**
 * 아이템 데이터 매니저 로그 헬퍼 라이브러리
 */
UCLASS()
class DUNGEONZERO_API UTSItemDataTableLogLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// 정적 데이터 로그 
	static void LogStaticItemData_Lib(FDZITemStaticData* InITemStaticData);
	
};
