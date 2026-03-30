// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZFindAnomalyMSG.generated.h"

// 이게 어노말리라고 생각함.
USTRUCT(BlueprintType)
struct FDZFindAnomalyMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AActor> FindAnomalyActor = nullptr;
};

// 찾기 결과
USTRUCT(BlueprintType)
struct FDZFindResultAnomalyMSG
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFindAnomaly = false;
};