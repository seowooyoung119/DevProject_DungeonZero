// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZStageMSG.generated.h"

// 스테이지 준비 시 호출
USTRUCT(BlueprintType)
struct FDZStageMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LoadStage = 0;
};

// 스테이지 준비 시 호출
USTRUCT(BlueprintType)
struct FDZStageRemainAnomalyMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StageRemainAnomaly = 0;
};
