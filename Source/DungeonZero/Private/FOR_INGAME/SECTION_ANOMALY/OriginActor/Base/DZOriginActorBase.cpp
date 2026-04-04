// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/OriginActor/Base/DZOriginActorBase.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZRegisterAllCanBeAnomalyActorHelperSystem.h"

//======================================================================================================================	
#pragma region 라이프_사이클

//──────────────
// 라이프 사이클 
//──────────────

class UDZRegisterAllCanBeAnomalyActorHelperSystem;

ADZOriginActorBase::ADZOriginActorBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;

	// rep
	bReplicates = true;
}

void ADZOriginActorBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ADZOriginActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Origin액터 등록
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem = UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(this);
	if (IsValid(RegisterAllCanBeAnomalyActorHelperSystem)) RegisterAllCanBeAnomalyActorHelperSystem->RegisterAllCanBeAnomalyActor(this);
	
	// 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	OriginVisibleListenerHandle = MessageSubsystem.RegisterListener<FDZOriginMSG>(DZ::OriginMSG::DZ_ORIGIN_VISIBILE_NOTICE, this, &ADZOriginActorBase::OnOriginVisibleReceived);

}

void ADZOriginActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(OriginVisibleListenerHandle);
	}
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region 게임_플레이_메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 플레이롤
	//━━━━━━━━━━━━━━━━━━━━	

void ADZOriginActorBase::OnOriginVisibleReceived(FGameplayTag Channel, const FDZOriginMSG& Payload)
{
	Execute_ToggleHiddenInGame(this, Payload.bIsVisible, Payload.bIsVisible);
}

#pragma endregion
//======================================================================================================================	
