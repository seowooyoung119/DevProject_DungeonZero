// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DZStageBalanceSetting.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName = "스테이지 밸런스 세팅"))
class DUNGEONZERO_API UDZStageBalanceSetting : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, DisplayName="스테이지 밸런스 데이터 테이블")
	TSoftObjectPtr<UDataTable> StageDataTable = nullptr;
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "어노말리 변환 데이터 테이블")
	TSoftObjectPtr<UDataTable> AnomalySettingTable;
};