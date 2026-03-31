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
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	TSoftObjectPtr<UTSItemTablesDataAsset> GlobalItemDataAsset = nullptr;
	
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	bool bWantPrintDeBugLog = false;
	
};