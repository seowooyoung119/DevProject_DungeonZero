// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Data/Table/DZAnomalySettingTable.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZChangeToAnomalyActorHelperSystem.generated.h"

/**
 * 역할 : 어노말리로 변할 수 있는 선정된 액터를 실제로 어노말리 액터로 변환 
 */
UCLASS()
class DUNGEONZERO_API UDZChangeToAnomalyActorHelperSystem : public UWorldSubsystem
{
	friend class UDZStageControlSystem;
	GENERATED_BODY()
//======================================================================================================================	
#pragma region Getter	
public:
	static UDZChangeToAnomalyActorHelperSystem* Get(const UObject* WorldContextObject);
#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
#pragma endregion	
//======================================================================================================================
#pragma region StageAPI
	/**
	 * @param SelectedActors 이전에 선택된 원본 액터들 (자동으로 부숨)
	 * @return 생성된 어노말리 액터들의 배열
	 */
	TArray<AActor*> ReplaceWithAnomalyActors_internal(const TArray<AActor*>& SelectedActors);
#pragma endregion	
//======================================================================================================================
#pragma region Data
	
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TMap<FName, FDZAnomalySettingTable> AnomalyDataMap;
	
#pragma endregion
//======================================================================================================================	
};
