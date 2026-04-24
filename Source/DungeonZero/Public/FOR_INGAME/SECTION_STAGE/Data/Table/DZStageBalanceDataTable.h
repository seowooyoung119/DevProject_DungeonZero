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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="플레이 인원")
	int32 PlayerNum = 4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="인원에 따른 플레이 시간")
	float Time = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="인원에 따른 어노말리 갯수")
	int32 AnomalyCount = 10;

};

