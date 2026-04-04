// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Control/DZStageControlSystem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAllowPlayerControlMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZDoorMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZOriginMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZChangeToAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZChooseBecomeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZRegisterAllCanBeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/DZStageBalanceDataModule.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"
#include "FOR_INGAME/SECTION_STAGE/System/Time/DZTimeReduceManager.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

UDZStageControlSystem* UDZStageControlSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZStageControlSystem* StageControlSystem = World->GetSubsystem<UDZStageControlSystem>();
	if (!IsValid(StageControlSystem)) return nullptr;
	
	return StageControlSystem;
}


#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	

	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━

void UDZStageControlSystem::PlayerEnterTheResultWay()
{
	UE_LOG(LogTemp, Warning, TEXT("1"))
	
	// 1. 모든 어노말리를 다 찾았는가?
	if (IsAllFound_internal() == false) ReStratLevel_internal();
	else StratNextLevel_internal();
	
	StopTimer_internal();
	ResetDoor_internal();
	
	// 2. 플레이어 처리 
	// 위치 이동 
	HandlePlayers_internal();
	
	// 3. 어노말리들 처리 
	HandleAnomalies_internal();
	
	// 3. 원본 액터들 처리
	HandleOriginActors_internal();
	
	// 4. 레벨에 따른 재시작 로직 시작
	RefreshAnomalyActors_internal();
	
	// 5. 남은 시간 갱신
	HandleRemainingTime_internal();
	
	// 6. 후 처리
	NoticeCurrentLevel_internal();
	AllowPlayerSeeAndMove_internal();
	AllowStartTimeTick_internal();
	
}

bool UDZStageControlSystem::IsAllFound_internal()
{
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return false;
	
	// 다 찾았는지 체크 
	UE_LOG(LogTemp, Warning, TEXT("2"))
	return  StageRuntimePlayDataModule->IsAllAnomalyHasBeenFound();
}

void UDZStageControlSystem::ReStratLevel_internal()
{
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	
	// 0으로 초기화
	UE_LOG(LogTemp, Warning, TEXT("3-a"))
	StageRuntimePlayDataModule->SetCurrentLevel(0);
}

void UDZStageControlSystem::StratNextLevel_internal()
{
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;

	// 다음 스테이로 증가
	int32 CurrentStageLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	++CurrentStageLevel;
	
	// 스테이지 증가 적용
	StageRuntimePlayDataModule->SetCurrentLevel(CurrentStageLevel);
	
	UE_LOG(LogTemp, Warning, TEXT("3-b"))
}

void UDZStageControlSystem::StopTimer_internal()
{
	UDZTimeReduceManager* TimeReduceManager = UDZTimeReduceManager::Get(this);
	if (!IsValid(TimeReduceManager)) return;
	
	// 타이머 중지
	TimeReduceManager->StopTime();
	
	// 시계 초기화
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZTimeMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::TimeMSG::DZ_TIME_TIMERESET, Payload);
	UE_LOG(LogTemp, Warning, TEXT("4"))
}

void UDZStageControlSystem::ResetDoor_internal()
{
	// 문 위치 초기화 
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZDoorMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::DoorMSG::DZ_DOOR_DOORRESET, Payload);
	UE_LOG(LogTemp, Warning, TEXT("5"))
}

void UDZStageControlSystem::HandlePlayers_internal()
{
	// 움직임 불가 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZAllowPlayerControlMSG Payload;
	Payload.CanMoveAndSee = false;
	MessageSubsystem.BroadcastMessage(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, Payload);
	
	// TODO : 위치 이동 
	
	UE_LOG(LogTemp, Warning, TEXT("6"))
}

void UDZStageControlSystem::HandleAnomalies_internal()
{
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;

	// 모든 어노말리 파괴
	for (auto& Anomaly : StageRuntimePlayDataModule->GetAnomalyActors())
	{
		if (!IsValid(Anomaly)) continue;
		
		Anomaly->Destroy();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("7"))
}

void UDZStageControlSystem::HandleOriginActors_internal()
{
	// 숨김 해제 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZOriginMSG Payload;
	Payload.bIsVisible = true;
	MessageSubsystem.BroadcastMessage(DZ::OriginMSG::DZ_ORIGIN_VISIBILE_NOTICE, Payload);
	
	UE_LOG(LogTemp, Warning, TEXT("8"))
}

void UDZStageControlSystem::RefreshAnomalyActors_internal()
{
	// 원본 액터들 가져오기
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem = UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(this);
	if (!IsValid(RegisterAllCanBeAnomalyActorHelperSystem))
	{
		UE_LOG(LogTemp, Warning, TEXT("RegisterAllCanBeAnomalyActorHelperSystem 게터 문제"))
		return;
	}
	TArray<AActor*>& Origins = RegisterAllCanBeAnomalyActorHelperSystem->GetPossibleActors();
	
	UE_LOG(LogTemp, Warning, TEXT("Origins %d"), Origins.Num())
	
	// 현재 레벨 가져오기
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule))
	{
		UE_LOG(LogTemp, Warning, TEXT("StageRuntimePlayDataModule 게터 문제"))
		return;
	}
	int32 CurrentStageLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	
	// 레벨에 따른 최소 최대 겟수
	UDZStageBalanceDataModule* StageBalanceDataModule = UDZStageBalanceDataModule::Get(this);
	if (!IsValid(StageBalanceDataModule))
	{
		UE_LOG(LogTemp, Warning, TEXT("StageBalanceDataModule 게터 문제"))
		return;
	}
	FDZStageBalanceRow* BalanceRow = StageBalanceDataModule->GetStageBalanceRow(CurrentStageLevel);
	if (!BalanceRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("BalanceRow 게터 문제"))
		return;
	}
	int32 MinCount = BalanceRow->MinAnomalyCount;
	int32 MaxCount = BalanceRow->MaxAnomalyCount;
	
	// 랜덤 고르기 실시 
	UDZChooseBecomeAnomalyActorHelperSystem* ChooseBecomeAnomalyActorHelperSystem = UDZChooseBecomeAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChooseBecomeAnomalyActorHelperSystem))
	{
		UE_LOG(LogTemp, Warning, TEXT("ChooseBecomeAnomalyActorHelperSystem 게터 문제"))
		return;
	}
	TArray<AActor*> SelectedActors = ChooseBecomeAnomalyActorHelperSystem->ChooseRandomAnomalyActors_internal(Origins, MinCount, MaxCount);
	
	UE_LOG(LogTemp, Warning, TEXT("SelectedActors %d"), SelectedActors.Num())
	
	// 변환 실시
	UDZChangeToAnomalyActorHelperSystem* ChangeToAnomalyActorHelperSystem = UDZChangeToAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChangeToAnomalyActorHelperSystem))
	{
		UE_LOG(LogTemp, Warning, TEXT("ChangeToAnomalyActorHelperSystem 게터 문제"))
		return;
	}
	TArray<AActor*> NewAnomalies = ChangeToAnomalyActorHelperSystem->ReplaceWithAnomalyActors_internal(SelectedActors);
	
	UE_LOG(LogTemp, Warning, TEXT("NewAnomalies %d"), NewAnomalies.Num())
	
	// 캐싱
	StageRuntimePlayDataModule->SetAnomalyActors(NewAnomalies);
	StageRuntimePlayDataModule->SetAnomalyCount(NewAnomalies.Num());
	
	UE_LOG(LogTemp, Warning, TEXT("9"))
}

void UDZStageControlSystem::HandleRemainingTime_internal()
{
	// 현재 레벨 가져오기
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	int32 CurrentStageLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	
	// 레벨에 따른 새로운 시간 가져오기
	UDZStageBalanceDataModule* StageBalanceDataModule = UDZStageBalanceDataModule::Get(this);
	if (!IsValid(StageBalanceDataModule)) return;
	FDZStageBalanceRow* BalanceRow = StageBalanceDataModule->GetStageBalanceRow(CurrentStageLevel);
	if (!BalanceRow) return;
	float NewTime = BalanceRow->Time;
	
	StageRuntimePlayDataModule->SetRemainingTime(NewTime);
	UE_LOG(LogTemp, Warning, TEXT("10"))
}

void UDZStageControlSystem::NoticeCurrentLevel_internal()
{
	// 현재 레벨 가져오기
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	int32 CurrentStageLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	
	// 레벨 번호 알림 
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZStageMSG Payload;
	Payload.LoadStage = CurrentStageLevel;
	MessageSubsystem.BroadcastMessage(DZ::StageMSG::DZ_STAGE_CURRENTLEVEL_NOTICE, Payload);
	
	UE_LOG(LogTemp, Warning, TEXT("11"))
}

void UDZStageControlSystem::AllowPlayerSeeAndMove_internal()
{
	// 움직임 가능 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZAllowPlayerControlMSG Payload;
	Payload.CanMoveAndSee = true;
	MessageSubsystem.BroadcastMessage(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, Payload);
	
	UE_LOG(LogTemp, Warning, TEXT("12"))
}

void UDZStageControlSystem::AllowStartTimeTick_internal()
{
	UDZTimeReduceManager* TimeReduceManager = UDZTimeReduceManager::Get(this);
	if (!IsValid(TimeReduceManager)) return;
	
	// 타이머 시작
	TimeReduceManager->StartTime();
	
	UE_LOG(LogTemp, Warning, TEXT("13"))
}



#pragma endregion
//======================================================================================================================	
	