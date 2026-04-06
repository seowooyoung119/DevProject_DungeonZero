// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DZItemPickUpSoundTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZItemPickUpSoundTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	int32 ItemID = -1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	TSoftObjectPtr<USoundBase> PickUpSound = nullptr;
	
};
