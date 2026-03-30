// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZTimeMSG.generated.h"

USTRUCT(BlueprintType)
struct FDZTimeMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RemainTime = 0;
};