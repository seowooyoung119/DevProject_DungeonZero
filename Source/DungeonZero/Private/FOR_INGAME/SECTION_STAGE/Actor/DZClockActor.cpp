// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZClockActor.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================	
#pragma region OnRep

void ADZClockActor::OnRep_TimeLeft()
{
	if (TimeLeft > 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("onRep : ClockActor 수신: 남은 시간 %.1f"), TimeLeft);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnRep : ClockActor 수신: 타임 오버!"));
	}
}

#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle
ADZClockActor::ADZClockActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void ADZClockActor::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	// 1. 타임 감소 구독
	TimeReduceListenerHandle = MessageSubsystem.RegisterListener<FDZTimeMSG>(DZ::Time::DZ_TIME_REDUCE, this, &ADZClockActor::OnTimeReduceReceived);
	// 2. 타임 오버 구독
	TimeOverListenerHandle = MessageSubsystem.RegisterListener<FDZTimeMSG>(DZ::Time::DZ_TIME_TIMEOVER, this, &ADZClockActor::OnTimeOverReceived);
}

void ADZClockActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZClockActor, TimeLeft);
}

void ADZClockActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
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
	UE_LOG(LogTemp, Warning, TEXT("ClockActor 수신: 남은 시간 %.1f"), TimeLeft);
}

void ADZClockActor::OnTimeOverReceived(FGameplayTag Channel, const FDZTimeMSG& Payload)
{
	TimeLeft = 0.0f;
	UE_LOG(LogTemp, Error, TEXT("ClockActor 수신: 타임 오버!"));
}

#pragma endregion
//======================================================================================================================	