// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Control/DZStageControlSystem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAllowPlayerControlMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZDoorMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZOriginMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/EndingMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
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
	
	// 타이머 처리, 문 처리, 드랍 아이템 처리, 데칼 액터 처리
	StopTimer_internal();
	ResetDoor_internal();
	GCDropItems_intenral();
	GCDecal_internal_ThisisTempAPI(); // TODO : 임시 데칼 갈비지 컬렉터 나중에 지우기
	
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

void UDZStageControlSystem::GCDecal_internal_ThisisTempAPI()
{
	if (!IsValid(GetWorld())) return;

	ADZDecalGarbageCollector* DecalGarbageCollector = Cast<ADZDecalGarbageCollector>(UGameplayStatics::GetActorOfClass(this, ADZDecalGarbageCollector::StaticClass()));
	if (!IsValid(DecalGarbageCollector)) return;
	DecalGarbageCollector->GCAllDecals();
}

void UDZStageControlSystem::HandlePlayers_internal()
{
	// 움직임 불가 알림
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZAllowPlayerControlMSG Payload;
	Payload.CanMoveAndSee = false;
	MessageSubsystem.BroadcastMessage(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, Payload);
	
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
	// 원본 액터들 가져오기
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem = UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(this);
	if (!IsValid(RegisterAllCanBeAnomalyActorHelperSystem)) return;
	TArray<AActor*>& Origins = RegisterAllCanBeAnomalyActorHelperSystem->GetPossibleActors();
	
	UE_LOG(LogTemp, Warning, TEXT("Origins %d"), Origins.Num())
	
	// 현재 레벨 가져오기
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	int32 CurrentStageLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	
	// 레벨에 따른 최소 최대 겟수
	UDZStageBalanceDataModule* StageBalanceDataModule = UDZStageBalanceDataModule::Get(this);
	if (!IsValid(StageBalanceDataModule)) return;
	FDZStageBalanceRow* BalanceRow = StageBalanceDataModule->GetStageBalanceRow(CurrentStageLevel);
	if (!BalanceRow) return;
	int32 MinCount = BalanceRow->MinAnomalyCount;
	int32 MaxCount = BalanceRow->MaxAnomalyCount;
	
	// 랜덤 고르기 실시 
	UDZChooseBecomeAnomalyActorHelperSystem* ChooseBecomeAnomalyActorHelperSystem = UDZChooseBecomeAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChooseBecomeAnomalyActorHelperSystem)) return;
	TArray<AActor*> SelectedActors = ChooseBecomeAnomalyActorHelperSystem->ChooseRandomAnomalyActors_internal(Origins, MinCount, MaxCount);
	
	// 변환 실시
	UDZChangeToAnomalyActorHelperSystem* ChangeToAnomalyActorHelperSystem = UDZChangeToAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChangeToAnomalyActorHelperSystem)) return;
	TArray<AActor*> NewAnomalies = ChangeToAnomalyActorHelperSystem->ReplaceWithAnomalyActors_internal(SelectedActors);
	
	UE_LOG(LogTemp, Warning, TEXT("NewAnomalies %d"), NewAnomalies.Num())
	
	// 캐싱
	StageRuntimePlayDataModule->SetAnomalyActors(NewAnomalies);
	StageRuntimePlayDataModule->SetAnomalyCount(NewAnomalies.Num());
	
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

void UDZStageControlSystem::AllowStartTimeTick_internal()
{
	UDZTimeReduceManager* TimeReduceManager = UDZTimeReduceManager::Get(this);
	if (!IsValid(TimeReduceManager)) return;
	
	// 타이머 시작
	TimeReduceManager->StartTime();
}



#pragma endregion
//======================================================================================================================	
	