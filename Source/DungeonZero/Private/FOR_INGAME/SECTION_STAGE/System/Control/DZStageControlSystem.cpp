// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Control/DZStageControlSystem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAIGCMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAllowPlayerControlMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZDoorMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZGameModeMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZOriginMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/EndingMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_AI/SpawnNode/DZSpawnNode.h"
#include "FOR_INGAME/SECTION_AI/System/DZAISpawnSystem.h"
#include "FOR_INGAME/SECTION_STAGE/Decal/DZDecalGarbageCollector.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZChangeToAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZChooseBecomeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZRegisterAllCanBeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/DZStageBalanceDataModule.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"
#include "FOR_INGAME/SECTION_STAGE/System/Item/DZDropItemGarbageCollectorSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Time/DZTimeReduceManager.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

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
	// 0. 마지막 스테이지 클리어했는가?
	if (IsAllFound_internal() == true && IsAllStageClear() == true)
	{
		DoEnding();
		return;
	}
	
	// 1. 모든 어노말리를 다 찾았는가?
	if (IsAllFound_internal() == false) ReStratLevel_internal();
	else StratNextLevel_internal();
	
	// 1.5 플레이어 처리 
	// 모든 플레이어 입력 멈춤 
	// 플레이어 암전 처리
	HandlePlayersInputAndSee_internal();
	
	// 2. 타이머 처리, 문 처리, 드랍 아이템 처리, 데칼 액터 처리, AI 처리, 죽음 체킹 초기화 처리
	StopTimer_internal();
	ResetDoor_internal();
	GCDropItems_intenral();
	GCDecal_internal_ThisIsTempAPI(); // 현재 안 쓰는 중 (쓰러면 레벨에 데칼 가비지 컬렉터 액터 배치 필요
	CGAIs_internal();
	GCFakeAnomalies_internal();
	CheckDeathReset_internal();
	
	// 1.5. 플레이어 처리 
	// 일정 딜레이 후 위치 이동 (암전 처리 클라 전파를 위한 시간 딜레이)
	FTimerHandle PlayerMoveTimerHandle; 
	GetWorld()->GetTimerManager().SetTimer(PlayerMoveTimerHandle, this, &UDZStageControlSystem::HandlePlayersLocation_internal, 3.0f, false);
	
	// 3. 어노말리들 처리 
	HandleAnomalies_internal();
	
	// 3. 원본 액터들 처리
	HandleOriginActors_internal();
	
	// 4. 레벨에 따른 재시작 로직 시작
	RefreshAnomalyActors_internal();
	
	// 5. 남은 시간 갱신
	HandleRemainingTime_internal();
	
	// 6. 후 처리

	// 레벨 번호 갱신
	NoticeCurrentLevel_internal(); 
	
	// 일정 딜레이 후 플레이어 암전 해제 및 입력 작동
	FTimerHandle TimerHandle; 
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDZStageControlSystem::AllowPlayerSeeAndMove_internal, 6.0f, false);
	
	// 타이머 시작은 문 열면 시작하도록 바꿈
}

bool UDZStageControlSystem::IsAllStageClear()
{
	// 런타임 모듈 가져오기 
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return false;
	
	// 레벨에 따른 새로운 시간 가져오기
	UDZStageBalanceDataModule* StageBalanceDataModule = UDZStageBalanceDataModule::Get(this);
	if (!IsValid(StageBalanceDataModule)) return false;
	
	int32 LastStageLevel = StageBalanceDataModule->GetLastStageLevel();
	int32 CurrentStageLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	
	return (LastStageLevel == CurrentStageLevel) ? true : false;
}

void UDZStageControlSystem::DoEnding()
{
	UDZTimeReduceManager* TimeReduceManager = UDZTimeReduceManager::Get(this);
	if (!IsValid(TimeReduceManager)) return;
	
	// 타이머 중지
	TimeReduceManager->StopTime();
	
	// 엔딩 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZEndingMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::EndingMSG::DZ_STAGE_ENDING_NOTICE, Payload);
}

bool UDZStageControlSystem::IsAllFound_internal()
{
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return false;
	
	// 다 찾았는지 체크 
	return  StageRuntimePlayDataModule->IsAllAnomalyHasBeenFound();
}

void UDZStageControlSystem::ReStratLevel_internal()
{
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	
	// 0으로 초기화
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
}

void UDZStageControlSystem::HandlePlayersInputAndSee_internal()
{
	// 움직임 불가, 시야 암전 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZAllowPlayerControlMSG Payload;
	Payload.CanMoveAndSee = false;
	MessageSubsystem.BroadcastMessage(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, Payload);
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
}

void UDZStageControlSystem::ResetDoor_internal()
{
	// 문 위치 초기화 
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZDoorMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::DoorMSG::DZ_DOOR_DOORRESET, Payload);
}

void UDZStageControlSystem::GCDropItems_intenral()
{
	// 드랍 아이템 전부 파괴 실시
	UDZDropItemGarbageCollectorSystem* DropItemGarbageCollectorSystem = UDZDropItemGarbageCollectorSystem::Get(this);
	if (!IsValid(DropItemGarbageCollectorSystem)) return;
	DropItemGarbageCollectorSystem->GCAllDropItems();
}

void UDZStageControlSystem::GCDecal_internal_ThisIsTempAPI()
{
	if (!IsValid(GetWorld())) return;

	ADZDecalGarbageCollector* DecalGarbageCollector = Cast<ADZDecalGarbageCollector>(UGameplayStatics::GetActorOfClass(this, ADZDecalGarbageCollector::StaticClass()));
	if (!IsValid(DecalGarbageCollector)) return;
	DecalGarbageCollector->GCAllDecals();
}

void UDZStageControlSystem::CGAIs_internal()
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZAIGCMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::AIMSG::DZ_SEND_AIGC, Payload);
	
}

void UDZStageControlSystem::GCFakeAnomalies_internal()
{
	// 스테이지 데이터 모듈 시스템 가져오기 
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	
	for (auto& FakeAnomaly : StageRuntimePlayDataModule->GetFakeAnomalyActors())
	{
		if (IsValid(FakeAnomaly))
		{
			FakeAnomaly->Destroy();
		}
	}
}

void UDZStageControlSystem::CheckDeathReset_internal()
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZGameModeDeathResetMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::GameModeMSG::DZ_GAMEMODE_DEADRESET, Payload);
	
}

void UDZStageControlSystem::HandlePlayersLocation_internal()
{
	// 위치 이동 :: 플레이어 스타트 인덱스 매칭하며 플레이어를 차례로 이동시킴 
	{
		TArray<AActor*> PlayerStarts;
		if (!IsValid(GetWorld())) return;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
	
		AGameStateBase* GameStateBase = UGameplayStatics::GetGameState(this);
		if (!IsValid(GameStateBase)) return;

		for (int32 Index = 0; Index < GameStateBase->PlayerArray.Num(); ++Index)
		{
			if (!GameStateBase->PlayerArray.IsValidIndex(Index)) continue;
		
			APlayerState* PlayerState = GameStateBase->PlayerArray[Index];
			if (!IsValid(PlayerState)) continue;
		
			APawn* PlayerPawn = PlayerState->GetPawn();
			if (!IsValid(PlayerPawn)) continue;
		
			FVector MoveLocation = PlayerStarts.IsValidIndex(Index) ? PlayerStarts[Index]->GetActorLocation() : PlayerStarts[0]->GetActorLocation();
			PlayerPawn->SetActorLocation(MoveLocation);
		}
	}
	
	// 혹시 모를 문 열림 방지 (문 초기화 재시도)
	ResetDoor_internal();
}

void UDZStageControlSystem::HandleAnomalies_internal()
{
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;

	// 모든 어노말리 파괴
	for (auto& Anomaly : StageRuntimePlayDataModule->GetAnomalyActorsForClearForNextStage())
	{
		if (!IsValid(Anomaly)) continue;
		
		Anomaly->Destroy();
	}
	
}

void UDZStageControlSystem::HandleOriginActors_internal()
{
	// 숨김 해제 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZOriginMSG Payload;
	Payload.bIsVisible = true;
	MessageSubsystem.BroadcastMessage(DZ::OriginMSG::DZ_ORIGIN_VISIBILE_NOTICE, Payload);
	
}

void UDZStageControlSystem::RefreshAnomalyActors_internal()
{
	//-----------------------------------
	// 원본 액터 목록 가져오기 
	//-----------------------------------

	// 원본 액터 등록 시스템 가져오기
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem = UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(this);
	if (!IsValid(RegisterAllCanBeAnomalyActorHelperSystem)) return;

	// 원본 액터들 가져오기
	TArray<AActor*>& Origins = RegisterAllCanBeAnomalyActorHelperSystem->GetPossibleActors();
	
	//-----------------------------------
	// 레벨에 따른 최소 최대 갯수 가져오기
	//-----------------------------------
	
	// 스테이지 데이터 모듈 시스템 가져오기 
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;

	// 현재 레벨 가져오기
	int32 CurrentStageLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	
	// 스테이지 밸런스 모듈 가져오기
	UDZStageBalanceDataModule* StageBalanceDataModule = UDZStageBalanceDataModule::Get(this);
	if (!IsValid(StageBalanceDataModule)) return;

	// 레벨에 맞는 밸런스 데이터 가져오기
	FDZStageBalanceRow* BalanceRow = StageBalanceDataModule->GetStageBalanceRow(CurrentStageLevel);
	if (!BalanceRow) return;

	// 레벨에 따른 최소 최대 겟수 (진짜)
	int32 MinCount = BalanceRow->MinAnomalyCount;
	int32 MaxCount = BalanceRow->MaxAnomalyCount;
	
	// 레벨에 따른 최소 최대 갯수 (가짜)
	int32 FakeMinCount = BalanceRow->MinFakeAnomalyCount;
	int32 FakeMaxCount = BalanceRow->MinFakeAnomalyCount;
	
	//-----------------------------------
	// 진짜 이상현 랜덤 고르기 실시 
	//-----------------------------------
	
	// 랜덤 고르기 시스템 가져오기 
	UDZChooseBecomeAnomalyActorHelperSystem* ChooseBecomeAnomalyActorHelperSystem = UDZChooseBecomeAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChooseBecomeAnomalyActorHelperSystem)) return;

	// 랜덤 고르기 실시
	TArray<AActor*> SelectedActors = ChooseBecomeAnomalyActorHelperSystem->ChooseRealAnomalyActors_internal(Origins, MinCount, MaxCount);
	
	// 변환 시스템 가져오기 
	UDZChangeToAnomalyActorHelperSystem* ChangeToAnomalyActorHelperSystem = UDZChangeToAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChangeToAnomalyActorHelperSystem)) return;
	
	// 변환 실시 (진짜)
	TArray<AActor*> NewAnomalies = ChangeToAnomalyActorHelperSystem->ReplaceWithRealAnomalyActors_internal(SelectedActors);
	
	//-----------------------------------
	// 가짜 이상현 랜덤 고르기 실시 
	//-----------------------------------
	
	// 랜덤 고르기 실시 (가짜)
	TArray<FDZFakeAnomalySeeInfo> SelectedFakeAnomalies = ChooseBecomeAnomalyActorHelperSystem->ChooseFakeAnomalyActors_internal(Origins, SelectedActors, FakeMinCount, FakeMaxCount);
	
	// 변환 실시 (가짜)
	TArray<AActor*> NewFakeAnomalies = ChangeToAnomalyActorHelperSystem->ReplaceWithFakeAnomalyActors_internal(SelectedFakeAnomalies);
	
	// 캐싱(확인용 어노말리 배열, 어노말리 카운트, 스테이지 클리어용 어노말리 배열)
	StageRuntimePlayDataModule->SetAnomalyActors(NewAnomalies);
	StageRuntimePlayDataModule->SetAnomalyCount(NewAnomalies.Num());
	StageRuntimePlayDataModule->SetAnomalyActorsForClearForNextStage(NewAnomalies);
	StageRuntimePlayDataModule->SetFakeAnomalyActors(NewFakeAnomalies);
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
}

void UDZStageControlSystem::AllowPlayerSeeAndMove_internal()
{
	// 움직임 가능 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZAllowPlayerControlMSG Payload;
	Payload.CanMoveAndSee = true;
	MessageSubsystem.BroadcastMessage(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, Payload);
}

void UDZStageControlSystem::AllowStartTimeTick()
{
	UDZTimeReduceManager* TimeReduceManager = UDZTimeReduceManager::Get(this);
	if (!IsValid(TimeReduceManager)) return;
	
	// 타이머 시작
	TimeReduceManager->StartTime();
	
	// 문 열 경우 AI 작동 시작 (AllowStartTimeTick 내부에서 호출)
	StartAI_Internal();
}

void UDZStageControlSystem::StartAI_Internal()
{
	if (!IsValid(GetWorld()))
	{
		return;
	}
	
	AActor* SpawnNode = UGameplayStatics::GetActorOfClass(this, ADZSpawnNode::StaticClass());
	if (!IsValid(SpawnNode))
	{
		return;
	}
	
	ADZSpawnNode* SpawnNodeCast = Cast<ADZSpawnNode>(SpawnNode);
	if (!IsValid(SpawnNodeCast))
	{
		return;
	}

	UDZAISpawnSystem* AISpawnSystem = UDZAISpawnSystem::Get(this);
	if (!IsValid(AISpawnSystem))
	{
		return;
	}
	
	FVector SpawnLocation = SpawnNodeCast->GetActorLocation();
	FRotator SpawnRotation = SpawnNodeCast->GetActorRotation();
	AISpawnSystem->SpawnNewAI(SpawnNodeCast->GetSpawnAIClassID(), SpawnLocation, SpawnRotation);
}


#pragma endregion
//======================================================================================================================	
	