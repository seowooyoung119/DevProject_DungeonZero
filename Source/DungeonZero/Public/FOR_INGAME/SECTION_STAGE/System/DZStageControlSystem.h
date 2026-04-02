// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_STAGE/Data/Table/DZStageBalanceDataTable.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZStageControlSystem.generated.h"

class UDZStageBalanceSetting;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZStageControlSystem : public UWorldSubsystem
{
	friend class ADZStageLoadUnLoadManager;
	friend class UDZTimeReduceManager;
	friend class UDZAnomalyFindHandleSystem;
	
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	static UDZStageControlSystem* Get(const UObject* WorldContextObject);
	
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
#pragma endregion	
//======================================================================================================================	
#pragma region StageAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━
public:
	//--------------
	// 새 게임 시 호출
	//--------------
	
	void StartGame();

	//--------------
	// 루프 
	//--------------
protected:
	// 스테이지 준비를 위한 초기화
	void PrepareStage_internal();
	
	// 스테이지 준비하기 (1단계 -> 룸 로드)
	void ReadyNewStage_internal_RoomLoad();
	
	// 스테이지 준비하기 (2단계 -> 원본 등록 가져오기) 
	void CallReadyNewStage_internal_GetAllOrigin();
	void DoReadyNewStage_internal_GetAllOrigin();
	
	// 스테이지 준비하기 (3단계 -> 최대 갯수, 최소 갯수 계산해서 랜덤하게 가져오기)
	void DoReadyNewStage_internal_GetRandomAnomalyActor();
	
	// 스테이지 준비하기 (4단계 -> 문을 열기, 타이머 돌리기)
	void DoReadyNewStage_internal_OpenDoor();
	void DoReadyNewStage_internal_StartTimer();
	
	// 스테이지 실행 
	// 1. 타이머는 알아서 이곳 시간 데이터를 깎는 중.
	// 2. 어노말리 찍으면 그 결과 처리는 어노말리 파인드 핸들 시스템이 처리하는 중.
	
	// 다 찾았으면 호출
	void DoRunningStage_Internal_HandleIfAllAnomalyFound();
	
#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	FDZStageBalanceRow* GetStageBalanceRow(const int32 StageLevel) { return StageDataMap.Find(StageLevel);};
	
protected:
	// 현재 스테이지 레벨 (기본 0)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	int32 CurrentStageLevel = 0;
	
	// 준비할 다음 스테이지 레벨 (기본 1)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	int32 NextStageLevel = 1;
	
	// 변환된 어노말리 갯수  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	int32 AnomalyCount = 0;
	
	// 원본 액터들 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> PossibleActors;
	
	// 변환 어노말리들
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> AnomalyActors;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	float RemainingTime = 0.0f;
	
	// 스테이지 밸런스 데이터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TMap<int32, FDZStageBalanceRow> StageDataMap;
	
#pragma endregion
//======================================================================================================================	
};
