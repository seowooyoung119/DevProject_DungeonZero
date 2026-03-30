// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/DZStageControlSystem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZDoorMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_ANOMALY/System/DZChangeToAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_ANOMALY/System/DZChooseBecomeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_ANOMALY/System/DZRegisterAllCanBeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/Library/StageBalanceDataLibrary.h"
#include "FOR_INGAME/SECTION_STAGE/System/DZTimeReduceManager.h"
#include "GameFramework/GameplayMessageSubsystem.h"

//======================================================================================================================	
#pragma region Getter
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
#pragma region LifeCycle

void UDZStageControlSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UStageBalanceDataLibrary::CacheStageDataToMap(StageDataMap);
	UStageBalanceDataLibrary::DebugLogStageMap(StageDataMap);
}

void UDZStageControlSystem::Deinitialize()
{
	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	}
	Super::Deinitialize();
}

#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	
void UDZStageControlSystem::StartGame()
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return;
	if (GetWorld()->GetNetMode() == NM_Client) return;
	
	UE_LOG(LogTemp, Warning, TEXT("StartGame : 스테이지 관리 매니저 : 게임 실시"));
	PrepareStage_internal();
}

void UDZStageControlSystem::PrepareStage_internal()
{
	// 기존 액터 부수기 (일단 부숨)
	for (auto& PossibleActor : PossibleActors)
	{
		if (IsValid(PossibleActor)) PossibleActor->Destroy();
	}
	for (auto& AnomalyActor : AnomalyActors)
	{
		if (IsValid(AnomalyActor)) AnomalyActor->Destroy();
	}
	// 초기화 
	PossibleActors.Empty();	
	AnomalyActors.Empty();
	AnomalyCount = 0;
	RemainingTime = 0.0f;
	
	// 초기화 실시 알림 메시지 보내기 (현재 레벨)
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZStageReadyMSG Payload;
	Payload.LoadStage = CurrentStageLevel;
	MessageSubsystem.BroadcastMessage(DZ::Stage::DZ_STAGE_PREPARE, Payload);
	
	UE_LOG(LogTemp, Warning, TEXT("PrepareStage : 스테이지 관리 매니저 : 초기화 알림 메시지 보냄"));
	
	// 3초 여유 준비 시작
	if (IsValid(GetWorld()))
	{
		FTimerHandle StagePrepareDelayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(StagePrepareDelayTimerHandle,this,&UDZStageControlSystem::ReadyNewStage_internal_RoomLoad,3.0f,false);
	}
}

void UDZStageControlSystem::ReadyNewStage_internal_RoomLoad()
{
	// 준비 실시 알림 메시지 보내기 (다음 레벨)
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZStageReadyMSG Payload;
	Payload.LoadStage = NextStageLevel;
	MessageSubsystem.BroadcastMessage(DZ::Stage::DZ_STAGE_READYNEWSTAGE, Payload);
	UE_LOG(LogTemp, Warning, TEXT("ReadyStage : 스테이지 관리 매니저 : 새 스테이지 준비 알림 메시지 보냄"));
}

void UDZStageControlSystem::CallReadyNewStage_internal_GetAllOrigin()
{
	// 3초 여유 후 캐싱 
	if (IsValid(GetWorld()))
	{
		FTimerHandle StagePrepareDelayTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(StagePrepareDelayTimerHandle,this,&UDZStageControlSystem::DoReadyNewStage_internal_GetAllOrigin,3.0f,false);
		UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 2단계 : 룸 로드 매니저 : 원본 액터 캐싱 실시"));
	}
}

void UDZStageControlSystem::DoReadyNewStage_internal_GetAllOrigin()
{
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem = UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(this);
	if (IsValid(RegisterAllCanBeAnomalyActorHelperSystem)) PossibleActors = RegisterAllCanBeAnomalyActorHelperSystem->PossibleActors;
	UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 2단계 : 룸 로드 매니저 : 원본 액터 캐싱 완료"));
	
	DoReadyNewStage_internal_GetRandomAnomalyActor();
}

void UDZStageControlSystem::DoReadyNewStage_internal_GetRandomAnomalyActor()
{
	UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 3단계 : 룸 로드 매니저 : 랜덤 뽑기 실시"));

	// 데이터 찾기 (다음 레벨)
	FDZStageBalanceRow* Row = StageDataMap.Find(NextStageLevel);
	if (Row == nullptr) return;

	// 랜덤 뽑기 
	UDZChooseBecomeAnomalyActorHelperSystem* ChooseBecomeAnomalyActorHelperSystem = UDZChooseBecomeAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChooseBecomeAnomalyActorHelperSystem)) return;
	TArray<AActor*> SelectedActors = ChooseBecomeAnomalyActorHelperSystem->ChooseRandomAnomalyActors_internal(PossibleActors, Row->MinAnomalyCount, Row->MaxAnomalyCount);
	
	UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 3단계 : 룸 로드 매니저 : 변환 실시"));
	
	// 변환 
	UDZChangeToAnomalyActorHelperSystem* ChangeToAnomalyActorHelperSystem = UDZChangeToAnomalyActorHelperSystem::Get(this);
	if (!IsValid(ChangeToAnomalyActorHelperSystem)) return;
	AnomalyActors = ChangeToAnomalyActorHelperSystem->ReplaceWithAnomalyActors_internal(SelectedActors);
	
	// 갯수 저장 
	AnomalyCount = AnomalyActors.Num();
	
	// 스테이지 값 갱신 (이제 다음 레벨이 준비가 끝났으므로 현재 레벨, 다음 레벨은 한칸 증가)
	CurrentStageLevel = NextStageLevel;
	NextStageLevel++;
	
	// 문 열고 타이머 돌리기 
	DoReadyNewStage_internal_OpenDoor();
	DoReadyNewStage_internal_StartTimer();
}

void UDZStageControlSystem::DoReadyNewStage_internal_OpenDoor()
{
	// 문 열기 알림 메시지 보내기 (이전 단계에서 스테이지 현재, 다음이 갱신되어 있어야 함)
	// 즉, 현재 레벨이 플레이어들이 깨야 하는 레벨임 == 문을 열어줘야 함)
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZDoorMSG Payload;
	Payload.StageLevel = CurrentStageLevel;
	Payload.bIsDoorOpen = true;
	MessageSubsystem.BroadcastMessage(DZ::Stage::DZ_STAGE_OPENDOOR, Payload);
	UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 3단계 : 룸 로드 매니저 : 문 열기 지시"));
}

void UDZStageControlSystem::DoReadyNewStage_internal_StartTimer()
{
	// 타이머 돌리기 메시지 보내기 (이전 단계에서 스테이지 현재, 다음이 갱신되어 있어야 함)
	// 즉, 현재 레벨이 플레이어들이 깨야 하는 레벨임 == 문을 열어줘야 함)
	FDZStageBalanceRow* Row = StageDataMap.Find(CurrentStageLevel);
	if (Row == nullptr) return;
	
	// 타이머 갱신 
	RemainingTime = Row->Time;
	
	// 타이머 감소 및 관리 넘기기 
	UDZTimeReduceManager* TimeReduceManager = UDZTimeReduceManager::Get(this);
	if (IsValid(TimeReduceManager)) TimeReduceManager->StartTime();
}

void UDZStageControlSystem::DoRunningStage_Internal_HandleIfAllAnomalyFound()
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZStageClearMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::Stage::DZ_STAGE_STAGECLAER, Payload);
	UE_LOG(LogTemp, Warning, TEXT("RunningStage 단계 : 스테이지 클리어"));
	
	// 타이머 멈추기
	UDZTimeReduceManager* TimeReduceManager = UDZTimeReduceManager::Get(this);
	if (IsValid(TimeReduceManager)) TimeReduceManager->StopTime();
	
	// 준비 시작 
	PrepareStage_internal();
}

#pragma endregion
//======================================================================================================================	
	