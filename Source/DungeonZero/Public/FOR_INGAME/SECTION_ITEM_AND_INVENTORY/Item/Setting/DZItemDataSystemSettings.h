// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DZItemDataSystemSettings.generated.h"

class UTSItemTablesDataAsset;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta=(DisplayName="아이템 데이터 세팅"))
class DUNGEONZERO_API UDZItemDataSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// 아이템 기본 정보 테이블 모음
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	TSoftObjectPtr<UDataTable> ItemInfoTable;

	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	bool bWantPrintDeBugLog = false;
	
};