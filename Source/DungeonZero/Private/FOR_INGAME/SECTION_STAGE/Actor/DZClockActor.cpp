// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZClockActor.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/DZStageBalanceDataModule.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"
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
}

void ADZClockActor::OnRep_CallPlayChimeSoundToClient()
{
	// 소리 재생
	if (IsValid(ChimeSound)) UGameplayStatics::PlaySoundAtLocation(this, ChimeSound, GetActorLocation());
}

void ADZClockActor::OnRep_CallPlayEndingSoundToClient()
{
	// 엔딩 사운드 재생 
	if (!IsValid(EndingChimeSound)) return;
	UGameplayStatics::PlaySoundAtLocation(this, EndingChimeSound, GetActorLocation());
	
	// 엔딩 사운드 반복 설정
	float SoundDuration = EndingChimeSound->GetDuration();
	GetWorldTimerManager().SetTimer(EndingTimerHandle, this, &ADZClockActor::PlayEndingChime, SoundDuration, true);
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
	
	// 시계 구성 (루트, 몸통, 시침, 분침
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(RootScene);
	HourHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HourHandMesh"));
	HourHandMesh->SetupAttachment(BodyMesh);
	MinuteHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MinuteHandMesh"));
	MinuteHandMesh->SetupAttachment(BodyMesh);
}

void ADZClockActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZClockActor, TimeLeft);
	DOREPLIFETIME(ADZClockActor, TotalDuration);
}
void ADZClockActor::BeginPlay()
{
	Super::BeginPlay();

	// 비주얼 초기화는 모두가 수행
	UpdateClockVisuals();

	// 서버에서만 메시지 시스템을 구독하여 '상태'를 관리함
	if (HasAuthority())
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		TimeResetListenerHandle = MessageSubsystem.RegisterListener<FDZTimeMSG>(DZ::TimeMSG::DZ_TIME_TIMERESET, this, &ADZClockActor::OnTimeResetReceived);
		TimeReduceListenerHandle = MessageSubsystem.RegisterListener<FDZTimeMSG>(DZ::TimeMSG::DZ_TIME_REDUCE, this, &ADZClockActor::OnTimeReduceReceived);
		TimeOverListenerHandle = MessageSubsystem.RegisterListener<FDZTimeMSG>(DZ::TimeMSG::DZ_TIME_TIMEOVER, this, &ADZClockActor::OnTimeOverReceived);
		EndingListenerHandle = MessageSubsystem.RegisterListener<FDZEndingMSG>(DZ::EndingMSG::DZ_STAGE_ENDING_NOTICE, this, &ADZClockActor::OnEndingReceived);
	}
}
void ADZClockActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(TimeReduceListenerHandle);
		MessageSubsystem.UnregisterListener(TimeOverListenerHandle);
		MessageSubsystem.UnregisterListener(TimeResetListenerHandle);
		MessageSubsystem.UnregisterListener(EndingListenerHandle);
	}
	// 타이머 해제
	if (IsValid(GetWorld())) GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region TimeAPI	

void ADZClockActor::OnTimeResetReceived(FGameplayTag Channel, const FDZTimeMSG& Payload)
{
	// 스테이지 데이터 모듈 체크
	UDZStageBalanceDataModule* StageBalanceDataModule = UDZStageBalanceDataModule::Get(this);
	if (!IsValid(StageBalanceDataModule)) return;

	// 스테이지 런타임 데이터 모듈 체크
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	
	// 현제 레벨에 맞는 데이터 가져오기 
	FDZStageBalanceRow* StageData = StageBalanceDataModule->GetStageBalanceRow(StageRuntimePlayDataModule->GetCurrentLevel());
	if (!StageData) return;
	TotalDuration = StageData->Time;
	
	// 1. 남은 시간을 데이터 시트에서 가져왔던 초기 전체 시간으로 복구
	TimeLeft = TotalDuration;

	// 2. 종소리 관련 기록도 초기화 (리셋 후 다시 1분 경과 시 소리가 나야 하므로)
	LastChimedMinute = -1;
	RemainingChimesToPlay = 0;
	GetWorldTimerManager().ClearTimer(ChimeTimerHandle);
	
	// 3. 비주얼 업데이트 실행 (TimeLeft == TotalDuration 이면 Progress가 0이 되어 12시 방향이 됨)
	UpdateClockVisuals();

}

void ADZClockActor::OnTimeReduceReceived(FGameplayTag Channel, const FDZTimeMSG& Payload)
{
	// 남은 시간 캐싱 및 onRep
	TimeLeft = Payload.RemainTime;
	
	// 비주얼 업데이트
	UpdateClockVisuals();
	
	// 종소리 업데이트
	CheckAndPlayChime(Payload.RemainTime);
}

void ADZClockActor::OnTimeOverReceived(FGameplayTag Channel, const FDZTimeMSG& Payload)
{
	// 남은 시간 캐싱 및 onRep
	TimeLeft = 0.0f;
	
	// 비주얼 업데이트
	UpdateClockVisuals();
}

void ADZClockActor::UpdateClockVisuals()
{
	// 0 미만 일경우 업데이트 안함
	if (TotalDuration <= 0.0f) return;

	// 분침 회전 계산: 12시(0도)에서 시작해서 시간이 흐를수록 360도로 회전
	float Progress = FMath::Clamp(1.0f - (TimeLeft / TotalDuration), 0.0f, 1.0f);
	float TargetRotation = -(Progress * 360.0f);

	// 회전각도 설정 
	if (MinuteHandMesh) MinuteHandMesh->SetRelativeRotation(FRotator(TargetRotation, 0.f, 0.f));
}

void ADZClockActor::CheckAndPlayChime(float NewTime)
{
	// 0 미만 일경우 업데이트 안함
	if (TotalDuration <= 0.0f) return;

	// 현재 경과된 "분" 계산 (예: 300초 전체에서 240초 남았으면 60초 경과 = 1분)
	float ElapsedTime = TotalDuration - NewTime;
	int32 CurrentElapsedMinute = FMath::FloorToInt(ElapsedTime / 60.0f);

	// 새로운 "분" 단계에 진입했고, 0분이 아닐 때 (1분 경과, 2분 경과...)
	if (CurrentElapsedMinute > LastChimedMinute && CurrentElapsedMinute > 0)
	{
		// 종소리 횟수 갱신
		LastChimedMinute = CurrentElapsedMinute;
        
		// 1분마다 종소리를 늘려감 (1분 경과시 1번, 2분 경과시 2번...)
		PlayChimeSound(CurrentElapsedMinute);
	}
}

void ADZClockActor::PlayChimeSound(int32 Count)
{
	if (!IsValid(ChimeSound) || Count <= 0) return;

	// 1. 재생해야 할 총 횟수 설정
	RemainingChimesToPlay = Count;

	// 첫 소리는 바로 나게
	PlaySingleChime();
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
	if (IsValid(ChimeSound)) UGameplayStatics::PlaySoundAtLocation(this, ChimeSound, GetActorLocation());

	// 카운트 감소
	--RemainingChimesToPlay;

	// 아직 더 울려야 한다면 타이머 재설정
	if (RemainingChimesToPlay > 0)
	{
		GetWorldTimerManager().SetTimer(ChimeTimerHandle, this, &ADZClockActor::PlaySingleChime, ChimeInterval, false);
	}
	
	// 클라이언트 전파
	++CallPlayChimeSoundToClient;
}


#pragma endregion
//======================================================================================================================
#pragma region EndingAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// EndingAPI
	//━━━━━━━━━━━━━━━━━━━━	

void ADZClockActor::OnEndingReceived(FGameplayTag Channel, const FDZEndingMSG& Payload)
{
	PlayEndingChime();
}

void ADZClockActor::PlayEndingChime()
{
	// 사운드 재생 타이머 중지
	GetWorldTimerManager().ClearTimer(ChimeTimerHandle);
	
	// 엔딩 사운드 재생 
	if (!IsValid(EndingChimeSound)) return;
	UGameplayStatics::PlaySoundAtLocation(this, EndingChimeSound, GetActorLocation());
	
	// 엔딩 사운드 반복 설정
	float GetSoundDuration = EndingChimeSound->GetDuration();
	GetWorldTimerManager().SetTimer(EndingTimerHandle, this, &ADZClockActor::PlayEndingChime, GetSoundDuration, true);
	
	// 클라이언트 전파
	++CallPlayEndingSoundToClient;
}

#pragma endregion
//======================================================================================================================