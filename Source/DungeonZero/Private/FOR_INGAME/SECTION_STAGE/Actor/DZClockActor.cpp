// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZClockActor.h"

#include "FOR_COMMON/SECTION_LOG/Stage/Clock/DZClockLOG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/DZStageControlSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================	
#pragma region OnRep

	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━

void ADZClockActor::OnRep_TimeLeft()
{
	
	// 1. 비주얼 업데이트 (바늘 돌리기)
	UpdateClockVisuals();
    
	// 2. 종소리 체크 (클라이언트에서도 소리가 나야 하므로)
	CheckAndPlayChime(TimeLeft);

	if (TimeLeft > 0.0f)
	{
		if (bWantPrintDebug) UE_LOG(DZCLockLog, Warning, TEXT("onRep : ClockActor 수신: 남은 시간 %.1f"), TimeLeft);
	}
	else
	{
		if (bWantPrintDebug) UE_LOG(DZCLockLog, Error, TEXT("OnRep : ClockActor 수신: 타임 오버!"));
	}
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

ADZClockActor::ADZClockActor()
{
	// tick 
	PrimaryActorTick.bCanEverTick = false;
	
	// network
	bReplicates = true;
	
	// 컴포넌트 구성
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootScene);

	HourHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HourHandMesh"));
	HourHandMesh->SetupAttachment(BodyMesh);

	MinuteHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteHandMesh"));
	MinuteHandMesh->SetupAttachment(BodyMesh);
}

void ADZClockActor::BeginPlay()
{
	Super::BeginPlay();

	// 자기 레벨에 맞는 데이터 캐싱 
	UDZStageControlSystem* StageControlSystem = UDZStageControlSystem::Get(this);
	if (!IsValid(StageControlSystem)) return;
	FDZStageBalanceRow* StageData = StageControlSystem->GetStageBalanceRow(TargetRoomLevel);
	if (!StageData) return;
	TotalDuration = StageData->Time;
	
	// 초기 12시 방향 세팅 (분침)
	UpdateClockVisuals();
	
	// 1. 타임 감소 구독
	// 2. 타임 오버 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	TimeReduceListenerHandle = MessageSubsystem.RegisterListener<FDZTimeMSG>(DZ::Time::DZ_TIME_REDUCE, this, &ADZClockActor::OnTimeReduceReceived);
	TimeOverListenerHandle = MessageSubsystem.RegisterListener<FDZTimeMSG>(DZ::Time::DZ_TIME_TIMEOVER, this, &ADZClockActor::OnTimeOverReceived);
}

void ADZClockActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZClockActor, TimeLeft);
}

void ADZClockActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(TimeReduceListenerHandle);
		MessageSubsystem.UnregisterListener(TimeOverListenerHandle);
	}
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region TimeAPI	
void ADZClockActor::OnTimeReduceReceived(FGameplayTag Channel, const FDZTimeMSG& Payload)
{
	if (bWantPrintDebug) UE_LOG(DZCLockLog, Warning, TEXT("ClockActor 수신: 남은 시간 %.1f"), TimeLeft);

	TimeLeft = Payload.RemainTime;
	UpdateClockVisuals();
	CheckAndPlayChime(TimeLeft);
}

void ADZClockActor::OnTimeOverReceived(FGameplayTag Channel, const FDZTimeMSG& Payload)
{
	if (bWantPrintDebug) UE_LOG(DZCLockLog, Error, TEXT("ClockActor 수신: 타임 오버!"));
	
	TimeLeft = 0.0f;
	UpdateClockVisuals();
}

void ADZClockActor::UpdateClockVisuals()
{
	if (TotalDuration <= 0.0f) return;

	// 분침 회전 계산: 12시(0도)에서 시작해서 시간이 흐를수록 360도로 회전
	// (1.0 - 비율)을 사용하면 시간이 줄어들수록 각도가 커짐.
	float Progress = FMath::Clamp(1.0f - (TimeLeft / TotalDuration), 0.0f, 1.0f);
	float TargetRotation = -(Progress * 360.0f);

	if (MinuteHandMesh)
	{
		// 시계가 놓인 방향(Yaw/Pitch/Roll)에 따라 달라지겠지만, 보통 시계 앞면 기준 Roll이나 Pitch를 조절하는데 여기서는 Y축(Pitch) 회전이라고 가정
		MinuteHandMesh->SetRelativeRotation(FRotator(TargetRotation, 0.f, 0.f));
	}
}

void ADZClockActor::CheckAndPlayChime(float NewTime)
{
	if (TotalDuration <= 0.0f) return;

	// 현재 경과된 "분" 계산 (예: 300초 전체에서 240초 남았으면 60초 경과 = 1분)
	float ElapsedTime = TotalDuration - NewTime;
	int32 CurrentElapsedMinute = FMath::FloorToInt(ElapsedTime / 60.0f);

	// 새로운 "분" 단계에 진입했고, 0분이 아닐 때 (1분 경과, 2분 경과...)
	if (CurrentElapsedMinute > LastChimedMinute && CurrentElapsedMinute > 0)
	{
		LastChimedMinute = CurrentElapsedMinute;
        
		UE_LOG(LogTemp, Warning, TEXT("T : %d"), LastChimedMinute);
		
		// 1분마다 종소리를 늘려감 (1분 경과시 1번, 2분 경과시 2번...)
		PlayChimeSound(CurrentElapsedMinute);
	}
}

void ADZClockActor::PlayChimeSound(int32 Count)
{
	if (!ChimeSound || Count <= 0) return;

	// 1. 재생해야 할 총 횟수 설정
	RemainingChimesToPlay = Count;

	// 2. 반복 재생
	GetWorldTimerManager().ClearTimer(ChimeTimerHandle);
    
	// 첫 소리는 바로 나게
	PlaySingleChime();

	if (bWantPrintDebug)
	{
		UE_LOG(DZCLockLog, Log, TEXT("종소리 울림! 횟수: %d"), Count);
	}
}

void ADZClockActor::PlaySingleChime()
{
	// 없으면 타이머 지우기
	if (RemainingChimesToPlay <= 0)
	{
		GetWorldTimerManager().ClearTimer(ChimeTimerHandle);
		return;
	}

	// 소리 재생
	UGameplayStatics::PlaySoundAtLocation(this, ChimeSound, GetActorLocation());

	// 로그
	if (bWantPrintDebug)
	{
		UE_LOG(DZCLockLog, Log, TEXT("종소리 재생 중... 남은 횟수: %d"), RemainingChimesToPlay - 1);
	}

	// 카운트 감소
	--RemainingChimesToPlay;

	// 아직 더 울려야 한다면 타이머 재설정
	if (RemainingChimesToPlay > 0)
	{
		GetWorldTimerManager().SetTimer(ChimeTimerHandle, this, &ADZClockActor::PlaySingleChime, ChimeInterval, false);
	}
	
}

#pragma endregion
//======================================================================================================================	