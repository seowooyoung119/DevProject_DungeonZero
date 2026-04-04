// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Data/Table/DZAnomalySettingTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DZAnomalyDataSystem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAnomalyDataSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	static UDZAnomalyDataSystem* Get(const UObject* InWorldContextObject);
	
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
	
public:
	FORCEINLINE	FDZAnomalySettingTable* GetTable(const FName& InAnomalyTag) { return AnomalyDataMap.Find(InAnomalyTag); };
	
protected:
	
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TMap<FName, FDZAnomalySettingTable> AnomalyDataMap;
	
#pragma endregion
//======================================================================================================================		
};
