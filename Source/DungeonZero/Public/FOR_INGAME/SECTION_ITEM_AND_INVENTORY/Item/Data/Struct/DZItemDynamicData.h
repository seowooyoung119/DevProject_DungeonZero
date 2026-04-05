// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "DZItemDynamicData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZItemDynamicData
{
	GENERATED_BODY()
	
	// 현재 스택 수 
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "DZ | Item")
	int32 CurrentStack = 0;
	
};
