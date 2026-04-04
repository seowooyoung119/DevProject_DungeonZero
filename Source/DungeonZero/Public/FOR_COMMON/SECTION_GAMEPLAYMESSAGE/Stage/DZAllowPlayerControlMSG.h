// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZAllowPlayerControlMSG.generated.h"

USTRUCT(BlueprintType)
struct FDZAllowPlayerControlMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanMoveAndSee = false;
};