// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZStageMSG.generated.h"

// 스테이지 준비 시 호출
USTRUCT(BlueprintType)
struct FDZStageReadyMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LoadStage = 0;
};

// 스테이지 클리어 시 호출
USTRUCT(BlueprintType)
struct FDZStageClearMSG
{
	GENERATED_BODY()
};
