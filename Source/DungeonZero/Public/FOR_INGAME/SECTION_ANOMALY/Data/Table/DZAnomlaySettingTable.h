// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DZAnomlaySettingTable.generated.h"

class ADZAnomalyActorBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZAnomlaySettingTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName= "원본 액터")
	TSubclassOf<ADZAnomalyActorBase> AnomalyClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName= "어노말리 액터")
	TSubclassOf<ADZAnomalyActorBase> AnomalyClass_Anomaly;
	
};
