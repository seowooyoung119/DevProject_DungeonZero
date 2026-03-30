// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZDoorMSG.generated.h"

// 스테이지 준비
USTRUCT(BlueprintType)
struct FDZDoorMSG
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 StageLevel = 0;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsDoorOpen = false;
};