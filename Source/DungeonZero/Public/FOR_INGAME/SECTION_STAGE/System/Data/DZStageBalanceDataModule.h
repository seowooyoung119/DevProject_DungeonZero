// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_STAGE/Data/Table/DZStageBalanceDataTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DZStageBalanceDataModule.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZStageBalanceDataModule : public UGameInstanceSubsystem
{
	GENERATED_BODY()
		
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	static UDZStageBalanceDataModule* Get(const UObject* InWorldContextObject);
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
#pragma endregion	
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	FDZStageBalanceRow* GetStageBalanceRow(const int32 StageLevel) { return StageDataMap.Find(StageLevel);};
	
	// 스테이지 밸런스 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TMap<int32, FDZStageBalanceRow> StageDataMap;
	
#pragma endregion
//======================================================================================================================	
};
