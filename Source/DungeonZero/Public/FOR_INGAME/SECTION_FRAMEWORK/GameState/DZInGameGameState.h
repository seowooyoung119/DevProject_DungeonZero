// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DZInGameGameState.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZInGameGameState : public AGameStateBase
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	// 데이터 모듈에 변환된 어노말리들이 있는지 체크하는 함수
	bool HandleIsThereAnyAnomaly(AActor* InTargetActor) { return AnomalyActors.Contains(InTargetActor);};
	
	// 어노말리를 찾았을 때 내부 데이터를 핸들하는 함수 
	FORCEINLINE void HandleOnFoundAnomaly(AActor* InTargetActor) { AnomalyActors.Remove(InTargetActor);}

	// 어노말리 갯수 확인하는 함수
	int32 GetAnomalyCount() const { return AnomalyActors.Num(); };
	
	// 어노말리 다 찾았는지 확인하는 함수
	FORCEINLINE bool IsAllAnomalyHasBeenFound() const { return  AnomalyActors.IsEmpty(); };
	
	// 들어온 숫자 만큼 남은 시간 차감하는 함수
	void ReduceRemainingTime(const int32& InAddReduceTime) { RemainingTime -= InAddReduceTime; };
	
	// 남은 시간 가져오기 및 세팅
	int32 GetRemainingTime() const { return RemainingTime; };
	void SetRemainingTime(const int32& InRemainingTimeNum) { RemainingTime = InRemainingTimeNum; };
	
protected:
	
	// 변환 어노말리들
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> AnomalyActors;
	
	// 남은 시간
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	float RemainingTime = 0.0f;
	
#pragma endregion
//======================================================================================================================
};
