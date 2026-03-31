// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "DZItemDynamicData.h"
#include "DZItemRuntimeData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZItemRuntimeData
{
	GENERATED_BODY()
	
	// 동적 데이터 
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "TS | Item")
	FDZItemDynamicData DynamicData;
	
	// 정적 데이터 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TS | Item")
	int32 StaticDataID = -1;
	
};
