// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DZAnomalySettingTable.generated.h"

class ADZOriginActorBase;

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZAnomalySettingTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName= "원본 액터")
	TSubclassOf<ADZOriginActorBase> AnomalyClass = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName= "어노말리 액터")
	TSubclassOf<AActor> AnomalyClass_Anomaly = nullptr;
	
};
