// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZDoorMSG.generated.h"

USTRUCT(BlueprintType)
struct FDZDoorMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDoorOpen = false;
};