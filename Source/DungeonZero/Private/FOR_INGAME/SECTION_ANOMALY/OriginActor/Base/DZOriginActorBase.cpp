// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/OriginActor/Base/DZOriginActorBase.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZRegisterAllCanBeAnomalyActorHelperSystem.h"
#include "GameFramework/GameNetworkManager.h"

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

bool ADZOriginActorBase::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (bAlwaysRelevant || IsOwnedBy(ViewTarget) || IsOwnedBy(RealViewer) || this == ViewTarget || ViewTarget == GetInstigator())
	{
		return true;
	}
	else if (bNetUseOwnerRelevancy && Owner)
	{
		return Owner->IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}
	else if (bOnlyRelevantToOwner)
	{
		return false;
	}
	else if (RootComponent && RootComponent->GetAttachParent() && RootComponent->GetAttachParent()->GetOwner() && (Cast<USkeletalMeshComponent>(RootComponent->GetAttachParent()) || (RootComponent->GetAttachParent()->GetOwner() == Owner)))
	{
		return RootComponent->GetAttachParent()->GetOwner()->IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}

	// 제거 목록  : 히든 및 콜리전 관련 체크 코드 
	// 사유 : 게임 로직 상 히든과 콜리전을 꺼도 복제가 되어야 함
	
	if (!RootComponent)
	{
		UE_LOG(LogNet, Warning, TEXT("Actor %s / %s has no root component in AActor::IsNetRelevantFor. (Make bAlwaysRelevant=true?)"), *GetClass()->GetName(), *GetName() );
		return false;
	}

	return !GetDefault<AGameNetworkManager>()->bUseDistanceBasedRelevancy || IsWithinNetRelevancyDistance(SrcLocation);
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
