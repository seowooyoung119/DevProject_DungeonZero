// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DZAISetting.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta=(DisplayName="AI 데이터 세팅"))
class DUNGEONZERO_API UDZAISetting : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	// AI 정보 테이블 모음
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	TSoftObjectPtr<UDataTable> AIInfoTable;
	
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	bool bWantPrintDeBugLog = false;
	
};
