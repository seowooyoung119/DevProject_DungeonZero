// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UDZStageRuntimePlayDataModule.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UUDZStageRuntimePlayDataModule : public UWorldSubsystem
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	static UUDZStageRuntimePlayDataModule* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	// 데이터 모듈에 변환된 어노말리들이 있는지 체크하는 함수
	bool HandleIsThereAnyAnomaly(AActor* InTargetActor);
	
	// 어노말리를 찾았을 때 내부 데이터를 핸들하는 함수 
	FORCEINLINE void HandleOnFoundAnomaly(AActor* InTargetActor) { --AnomalyCount; }
	
	// 어노말리 다 찾았는지 확인하는 함수
	FORCEINLINE bool IsAllAnomalyHasBeenFound() const { return  AnomalyCount == 0 ? true : false; };

	
	
	// 들어온 숫자 만큼 남은 시간 차감하는 함수
	void ReduceRemainingTime(const int32& InAddReduceTime) { RemainingTime -= InAddReduceTime; };
	
	
	// 현재 레벨 데이터 가져오기 및 세팅
	int32 GetCurrentLevel() const { return CurrentStageLevel; };
	void SetCurrentLevel(const int32& InCurrentLevel) { CurrentStageLevel = InCurrentLevel; };
	
	// 변환된 어노말리 갯수 가져오기 및 세팅
	int32 GetAnomalyCount() const { return AnomalyCount; };
	void SetAnomalyCount(const int32& InNewAnomalyCountNum) { AnomalyCount = InNewAnomalyCountNum; };
	
	// 변환 어노말리 가져오기 및 세팅
	TArray<AActor*> GetAnomalyActors() { return AnomalyActors; };
	void SetAnomalyActors(const TArray<AActor*>& InArray) { AnomalyActors.Empty(); AnomalyActors = InArray; };
	
	// 남은 시간 가져오기 및 세팅
	int32 GetRemainingTime() const { return RemainingTime; };
	void SetRemainingTime(const int32& InRemainingTimeNum) { RemainingTime = InRemainingTimeNum; };
	
	
	
protected:
	// 현재 스테이지 레벨 (기본 0)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	int32 CurrentStageLevel = 0;
	
	// 변환된 어노말리 갯수  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	int32 AnomalyCount = 999;
	
	// 변환 어노말리들
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> AnomalyActors;
	
	// 남은 시간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	float RemainingTime = 0.0f;
	
#pragma endregion
//======================================================================================================================	
};
