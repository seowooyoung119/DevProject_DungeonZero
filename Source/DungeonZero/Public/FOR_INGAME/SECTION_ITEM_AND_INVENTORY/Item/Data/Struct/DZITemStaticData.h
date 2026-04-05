// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/DataTable/DZItemInfoTable.h"
#include "DZITemStaticData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZITemStaticData
{
	GENERATED_BODY()
	
	// 아이템 정보 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Item")
	FDZItemInfoTable ItemStaticInfo;
};
