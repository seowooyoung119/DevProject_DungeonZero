// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DZItemDropSoundTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZItemDropSoundTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	int32 ItemID = -1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	TSoftObjectPtr<USoundBase> DropSound = nullptr;
	
};
