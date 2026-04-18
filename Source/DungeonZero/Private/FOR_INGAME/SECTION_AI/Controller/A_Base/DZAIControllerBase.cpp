// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/Controller/A_Base/DZAIControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/StateTreeAIComponent.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_AI/Library/DZStateTreeLibrary.h"
#include "Navigation/CrowdFollowingComponent.h"


ADZAIControllerBase::ADZAIControllerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADZAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	UCrowdFollowingComponent* CrowdFollowingComponent = FindComponentByClass<UCrowdFollowingComponent>();
	if (IsValid(CrowdFollowingComponent))
	{
		CrowdFollowingComponent->SetCrowdSeparation(true);
		CrowdFollowingComponent->SetCrowdSeparationWeight(50.f);
		CrowdFollowingComponent->SetCrowdAvoidanceRangeMultiplier(1.f);
	}	
	
	// GC 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	OnGCCallListenerHandle = MessageSubsystem.RegisterListener<FDZAIGCMSG>(DZ::AIMSG::DZ_SEND_AIGC, this, &ADZAIControllerBase::OnGCCallReceived);
}

void ADZAIControllerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		if (OnGCCallListenerHandle.IsValid()) MessageSubsystem.UnregisterListener(OnGCCallListenerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
}

void ADZAIControllerBase::OnGCCallReceived(FGameplayTag Channel, const FDZAIGCMSG& Payload)
{
	if (!IsValid(GetPawn()))
	{
		return;
	}
	
	// GAS 멈추기 
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (IsValid(ASC))
	{
		ASC->CancelAllAbilities();
	}
	
	// 스테이트 트리 멈추기
	UStateTreeAIComponent* StateTreeAIComponent = UDZStateTreeLibrary::GetStateTreeComponentFromController(this);
	if (IsValid(StateTreeAIComponent))
	{
		FString Reason(TEXT("GC Call Received"));
		StateTreeAIComponent->StopLogic(Reason);
	}
	
	// 움직임 멈추기
	StopMovement();
	
	// 소유 중인 폰 지우기 
	GetPawn()->Destroy();
	
	// 자기 자신도 지우기
	Destroy();
}
