// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/DZTimeReduceManager.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/DZStageControlSystem.h"
#include "GameFramework/GameplayMessageSubsystem.h"

//======================================================================================================================	
#pragma region Getter
UDZTimeReduceManager* UDZTimeReduceManager::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZTimeReduceManager* TimeReduceManager = World->GetSubsystem<UDZTimeReduceManager>();
	if (!IsValid(TimeReduceManager)) return nullptr;
	
	return TimeReduceManager;
}
#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle

void UDZTimeReduceManager::Deinitialize()
{
	if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	Super::Deinitialize();
}
#pragma endregion
//======================================================================================================================	
#pragma region TimeReduceAPI

void UDZTimeReduceManager::StartTime()
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return;
	if (GetWorld()->GetNetMode() == NM_Client) return;
	
	if (TimerHandle.IsValid()) TimerHandle.Invalidate();
	
	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDZTimeReduceManager::TimeReduceHandle, 1.0f, true);
	}
}

void UDZTimeReduceManager::StopTime()
{
	if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
}

void UDZTimeReduceManager::TimeReduceHandle()
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return;
	if (GetWorld()->GetNetMode() == NM_Client) return;
	
	UDZStageControlSystem* StageControlSystem = UDZStageControlSystem::Get(this);
	if (!IsValid(StageControlSystem)) return;
	
	// 시간이 남은 경우
	if (StageControlSystem->RemainingTime > 0.0f)
	{
		// 줄이기 로직 실행 
		StageControlSystem->RemainingTime -= 1.0f;
		
		// 메시지 보내기
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZTimeMSG Payload;
		Payload.RemainTime = StageControlSystem->RemainingTime;
		MessageSubsystem.BroadcastMessage(DZ::Time::DZ_TIME_REDUCE, Payload);
		UE_LOG(LogTemp, Warning, TEXT("RunningStage 단계 : 타임 감소 매니저 타임 감소 진행 : %.1f"), StageControlSystem->RemainingTime);
	}
	// 타임 오버인 경우 
	else
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZTimeMSG Payload;
		Payload.RemainTime = 0.0f;
		MessageSubsystem.BroadcastMessage(DZ::Time::DZ_TIME_TIMEOVER, Payload);
		UE_LOG(LogTemp, Error, TEXT("RunningStage 단계 : 타임 감소 매니저 타임 오버!"));
		if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

#pragma endregion
//======================================================================================================================	