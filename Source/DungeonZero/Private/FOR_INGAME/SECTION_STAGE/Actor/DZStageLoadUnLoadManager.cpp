// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZStageLoadUnLoadManager.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/DZStageControlSystem.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Kismet/GameplayStatics.h"

//======================================================================================================================	
#pragma region LifeCycle

ADZStageLoadUnLoadManager::ADZStageLoadUnLoadManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADZStageLoadUnLoadManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 구독 : 초기화
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	ReadyNewStageListenerHandle = MessageSubsystem.RegisterListener<FDZStageMSG>(DZ::Stage::DZ_STAGE_PREPARE, this, &ADZStageLoadUnLoadManager::OnPrepareMessageReceived);
	
	// 구독 : 준비 
	ReadyNewStageListenerHandle = MessageSubsystem.RegisterListener<FDZStageMSG>(DZ::Stage::DZ_STAGE_READYNEWSTAGE, this, &ADZStageLoadUnLoadManager::OnReadyNewStageMessageReceived);
}

void ADZStageLoadUnLoadManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 메시지 시스템 구독 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(ReadyNewStageListenerHandle);
	}
	Super::EndPlay(EndPlayReason);
}


#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	

// 준비 전 초기화 (들어온 레벨 언로드 실시)
void ADZStageLoadUnLoadManager::OnPrepareMessageReceived(FGameplayTag GameplayTag, const FDZStageMSG& Payload)
{
	// // 서버에서 실행
	// if (!HasAuthority()) return;
	//
	// // 찾기 
	// auto FoundLevelPtr = LevelToLoad.Find(Payload.LoadStage);
	// if (FoundLevelPtr  == nullptr) return;
	// auto FoundLevel =  *FoundLevelPtr;
	// if (FoundLevel.IsNull()) return;
	//
	// // 레벨 이름 추출
	// FName LevelName = FName(*FoundLevel.GetAssetName());
	//
	// // 레벨 언로드 호출
	// UGameplayStatics::UnloadStreamLevel(this, LevelName, FLatentActionInfo(),false );
	// UE_LOG(LogTemp, Warning, TEXT("Prepare : 룸 로드 매니저 : 언로드 실시"));;
}

//  (1단계 -> 룸 로드 -> 2단계 요청 실시)
void ADZStageLoadUnLoadManager::OnReadyNewStageMessageReceived(FGameplayTag Channel, const FDZStageMSG& Payload)
{
	// 서버에서 실행
	if (!HasAuthority()) return;
	
	// 찾기 
	auto FoundLevelPtr = LevelToLoad.Find(Payload.LoadStage);
	if (FoundLevelPtr  == nullptr) return;
	auto FoundLevel =  *FoundLevelPtr;
	if (FoundLevel.IsNull()) return;
	
	// 레벨 이름 추출
	FName LevelName = FName(*FoundLevel.GetAssetName());

	// 콜백 설정
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnReadyNewStageLoadingFinished");
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	// 레벨 로드 호출
	UGameplayStatics::LoadStreamLevel(this, LevelName, true,   false, LatentInfo);
	UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 1단계 : 룸 로드 매니저 : 로드 실시"));
}
void ADZStageLoadUnLoadManager::OnReadyNewStageLoadingFinished()
{
	// 2단계 요청 
	UDZStageControlSystem* StageControlSystem = UDZStageControlSystem::Get(this);
	StageControlSystem->CallReadyNewStage_internal_GetAllOrigin();
	UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 1단계 : 룸 로드 매니저 : 로드 완료"));
}

#pragma endregion
//======================================================================================================================	