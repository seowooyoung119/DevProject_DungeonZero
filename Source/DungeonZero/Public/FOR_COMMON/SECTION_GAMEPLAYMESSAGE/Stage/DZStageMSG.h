// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZStageMSG.generated.h"

// 스테이지 준비
USTRUCT(BlueprintType)
struct FDZStageMSG
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 LoadStage = 0;
};