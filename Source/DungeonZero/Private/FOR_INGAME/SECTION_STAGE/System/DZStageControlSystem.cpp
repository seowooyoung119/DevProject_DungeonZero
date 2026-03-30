// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/DZStageControlSystem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_ANOMALY/System/DZChangeToAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_ANOMALY/System/DZChooseBecomeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_ANOMALY/System/DZRegisterAllCanBeAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_STAGE/Library/StageBalanceDataLibrary.h"
#include "FOR_INGAME/SECTION_STAGE/Setting/DZStageBalanceSetting.h"
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

void UDZStageControlSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UStageBalanceDataLibrary::CacheStageDataToMap(StageDataMap);
	UStageBalanceDataLibrary::DebugLogStageMap(StageDataMap);
}

void UDZStageControlSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}
#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle
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
	UE_LOG(LogTemp, Warning, TEXT("StartGame : 스테이지 관리 매니저 : 게임 실시"));
	PrepareStage_internal();
}

void UDZStageControlSystem::PrepareStage_internal()
{
	// 데이터 초기화
	PossibleActors.Empty();	
	AnomalyActors.Empty();
	AnomalyCount = 0;
	
	// 초기화 실시 알림 메시지 보내기
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZStageMSG Payload;
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
	// 준비 실시 알림 메시지 보내기
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZStageMSG Payload;
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

	// 데이터 찾기
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
	
	
}
#pragma endregion
//======================================================================================================================	
	