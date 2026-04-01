// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZClockActor.h"

#include "FOR_COMMON/SECTION_LOG/Stage/Clock/DZClockLOG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================	
#pragma region OnRep

	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━

void ADZClockActor::OnRep_TimeLeft()
{
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
}

void ADZClockActor::BeginPlay()
{
	Super::BeginPlay();

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
	TimeLeft = Payload.RemainTime;
	if (bWantPrintDebug) UE_LOG(DZCLockLog, Warning, TEXT("ClockActor 수신: 남은 시간 %.1f"), TimeLeft);
}

void ADZClockActor::OnTimeOverReceived(FGameplayTag Channel, const FDZTimeMSG& Payload)
{
	TimeLeft = 0.0f;
	if (bWantPrintDebug) UE_LOG(DZCLockLog, Error, TEXT("ClockActor 수신: 타임 오버!"));
}

#pragma endregion
//======================================================================================================================	