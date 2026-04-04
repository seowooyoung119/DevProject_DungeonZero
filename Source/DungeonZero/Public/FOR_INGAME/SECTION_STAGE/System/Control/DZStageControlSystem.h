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
#pragma region StageAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━
public:

	// 플레이어가 스테이지 결과 통로로 들어갔을 때 호출 
	// NOTE : 맨처음 플레이에도 호출됨
	UFUNCTION(BlueprintCallable)
	void PlayerEnterTheResultWay();
	
protected:
	
	// 1. 모든 어노말리를 다 찾았는가?
	bool IsAllFound_internal();
	
	// CASE A : 다 찾지 않음
	// 기존 레벨 초기화 (레벨 num을 0로 만듬)
	void ReStratLevel_internal();
	
	// CASE B : 다 찾음
	// 다음 레벨 시작 (레벨 num만 갱신 후 이후 로직은 전부 같음)
	void StratNextLevel_internal();
	
	// 타이머 및 문 처리
	void StopTimer_internal();
	void ResetDoor_internal();
	
	// 2. 플레이어 처리 
	// 모든 플레이어 입력 멈춤 
	// 플레이어 암전 처리
	// 위치 이동 
	void HandlePlayers_internal();
	
	// 3. 어노말리들 처리
	// 모든 어노말리 파괴
	// 데이터 모듈의 어노말리 배열 초기화, 숫자 초기화
	void HandleAnomalies_internal();
	
	// 3. 원본 액터들 처리 
	// 숨김 처리 해제
	void HandleOriginActors_internal();
	
	// 4. 레벨에 따른 재시작 로직 시작
	// 원본 중에 랜덤하게 고르기 (현재 레벨에 따라서 데이터에 맞게)
	// 어노 말리로 변환 (원본은 숨김 처리)
	// 데이터 모듈의 어노말리 배열, 갯수 갱신
	void RefreshAnomalyActors_internal();
	
	// 5. 남은 시간 갱신 
	// 남은 시간 새로 갱신 (데이터에 맞게)
	void HandleRemainingTime_internal();
	
	// 6. 후 처리 
	// 레벨 번호 알림
	// 플레이어 암전 해제 및 입력 작동
	// 타이머 시작
	void NoticeCurrentLevel_internal();
	void AllowPlayerSeeAndMove_internal();
	void AllowStartTimeTick_internal();
	
#pragma endregion
//======================================================================================================================	
};
