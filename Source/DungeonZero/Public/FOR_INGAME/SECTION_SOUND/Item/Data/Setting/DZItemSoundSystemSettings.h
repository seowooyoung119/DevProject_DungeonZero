// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DZItemSoundSystemSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta=(DisplayName="아이템 사운드 데이터 세팅"))
class DUNGEONZERO_API UDZItemSoundSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	// 아이템 픽업 사운드 정보 테이블 모음
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	TSoftObjectPtr<UDataTable> ItemPickSoundInfoTable = nullptr;
	
	// 아이템 드랍 사운드 정보 테이블 모음
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	TSoftObjectPtr<UDataTable> ItemDropSoundInfoTable = nullptr;
	
	UPROPERTY(Config, EditAnywhere, Category = "ItemData")
	bool bWantPrintDeBugLog = false;
		
};
