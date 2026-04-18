// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DZAIClassTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZAIClassTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Class")
	int32 AIClassID = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Class")
	TSubclassOf<AActor> AIClass = nullptr;
	
};
