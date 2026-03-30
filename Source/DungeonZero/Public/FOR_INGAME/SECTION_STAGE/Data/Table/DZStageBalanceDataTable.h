// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DZStageBalanceDataTable.generated.h"

USTRUCT(BlueprintType)
struct FDZStageBalanceRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="룸")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="시간")
	float Time = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="최소 어노말리 갯수")
	int32 MinAnomalyCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="최대 어노말리 갯수")
	int32 MaxAnomalyCount = 5;
};
