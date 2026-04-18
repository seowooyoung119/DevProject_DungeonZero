// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
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
	// 0. 마지막 스테이지를 클리어 했는지 알아보고 실행
	bool IsAllStageClear();
	void DoEnding();
	
	// 1. 모든 어노말리를 다 찾았는가?
	bool IsAllFound_internal();
	
	// CASE A : 다 찾지 않음
	// 기존 레벨 초기화 (레벨 num을 0로 만듬)
	void ReStratLevel_internal();
	
	// CASE B : 다 찾음
	// 다음 레벨 시작 (레벨 num만 갱신 후 이후 로직은 전부 같음)
	void StratNextLevel_internal();
	
	// 1.5. 플레이어 처리 
	// 위치 이동 
	void HandlePlayersInputAndSee_internal();
	
	// 2. 타이머 처리, 문 처리, 드랍 아이템 처리, 데칼 액터 처리, AI 처리, 죽음 체킹 초기화 처리
	void StopTimer_internal();
	void ResetDoor_internal();
	void GCDropItems_intenral();
	void GCDecal_internal_ThisIsTempAPI();	// 현재 안 쓰는 중 (쓰러면 레벨에 데칼 가비지 컬렉터 액터 배치 필요
	void CGAIs_internal();
	void CheckDeathReset_internal();
	
	// 2.5위치 이동 
	void HandlePlayersLocation_internal();
	
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
	// 일정 딜레이 후 플레이어 암전 해제 및 입력 작동 및 죽음 초기화
	void NoticeCurrentLevel_internal();
	void AllowPlayerSeeAndMove_internal();
	
public:
	// 7. 후 처리
	// 타이머 시작 (문 열면 시작하도록 바꿈)
	void AllowStartTimeTick();
	
protected:
	// 문 열 경우 AI 작동 시작 (AllowStartTimeTick 내부에서 호출)
	void StartAI_Internal();
	
#pragma endregion
//======================================================================================================================	
};
