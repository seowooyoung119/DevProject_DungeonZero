// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Time/DZTimeReduceManager.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "FOR_COMMON/SECTION_LOG/Stage/System/DZStageSystemLOG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"
#include "GameFramework/GameplayMessageSubsystem.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

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
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

void UDZTimeReduceManager::Deinitialize()
{
	if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	Super::Deinitialize();
}
#pragma endregion
//======================================================================================================================	
#pragma region TimeReduceAPI

	//━━━━━━━━━━━━━━━━━━━━
	// TimeReduceAPI
	//━━━━━━━━━━━━━━━━━━━━

void UDZTimeReduceManager::StartTime()
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return;
	if (GetWorld()->GetNetMode() == NM_Client) return;
	
	// 타이머 핸들 초기화
	if (TimerHandle.IsValid()) TimerHandle.Invalidate();
	
	// 시작 
	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDZTimeReduceManager::TimeReduceHandle, 1.0f, true);
	}
}

void UDZTimeReduceManager::StopTime()
{
	// 타이머 제거 
	if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
}

void UDZTimeReduceManager::TimeReduceHandle()
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return;
	if (GetWorld()->GetNetMode() == NM_Client) return;
	
	// 데이터 모듈 가져오기 
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	
	// 시간이 남은 경우
	if (StageRuntimePlayDataModule->GetRemainingTime() > 0.0f)
	{
		// 줄이기 로직 실행 
		StageRuntimePlayDataModule->ReduceRemainingTime(1.0f);
		
		// 메시지 보내기
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZTimeMSG Payload;
		Payload.RemainTime = StageRuntimePlayDataModule->GetRemainingTime();
		MessageSubsystem.BroadcastMessage(DZ::TimeMSG::DZ_TIME_REDUCE, Payload);
	}
	
	// 타임 오버인 경우 
	else
	{
		// 메시지 보내기
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZTimeMSG Payload;
		Payload.RemainTime = 0.0f;
		MessageSubsystem.BroadcastMessage(DZ::TimeMSG::DZ_TIME_TIMEOVER, Payload);
		
		// 타이머 종료 
		if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}

#pragma endregion
//======================================================================================================================	