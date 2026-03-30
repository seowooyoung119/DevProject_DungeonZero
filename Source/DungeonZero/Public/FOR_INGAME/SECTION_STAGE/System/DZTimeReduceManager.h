// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZTimeReduceManager.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZTimeReduceManager : public UWorldSubsystem
{
	friend class UDZStageControlSystem;
	
	GENERATED_BODY()
//======================================================================================================================	
#pragma region Getter
public:
	static UDZTimeReduceManager* Get(const UObject* WorldContextObject);
#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle
public:
	virtual void Deinitialize() override;
#pragma endregion
//======================================================================================================================	
#pragma region TimeReduceAPI
protected:
	// 타이머 시작
	void StartTime();
	
	// 타이머 종료 또는 취소
	void StopTime();
	
	// 타이머 째각째각
	UFUNCTION()
	void TimeReduceHandle();
#pragma endregion
//======================================================================================================================
#pragma region Data
protected:
	
	// 관리 타이머
	FTimerHandle TimerHandle;
	
#pragma endregion
//======================================================================================================================		
};
