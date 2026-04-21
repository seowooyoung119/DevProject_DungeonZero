// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "AbilitySystemComponent.h"
#include "FOR_INGAME/SECTION_ANOMALY/Comp/DZAnomalyTriggerComponent.h"
#include "Net/UnrealNetwork.h"


//======================================================================================================================	
#pragma region 라이프_사이클

//──────────────
// 라이프 사이클 
//──────────────

ADZAnomalyActorBase::ADZAnomalyActorBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;

	// rep
	bReplicates = true;
	SetReplicatingMovement(true);
	
	AnomalyAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(
		TEXT("AnomalyAbilitySystemComponent"));
	AnomalyAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ADZAnomalyActorBase::BeginPlay()
{
	Super::BeginPlay();

	AnomalyAbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	if (!HasAuthority() || !IsValid(AnomalyGameplayAbility))
	{
		return;
	}

	// 어노말리 GA 랜덤 부여
	InitGAS_internal(AnomalyAbilitySystemComponent);
	
	// 어노말리 GA 활성화 설정
	ActivateAnomaly_internal(AnomalyAbilitySystemComponent);
}

void ADZAnomalyActorBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZAnomalyActorBase, FakeAnomalySeeInfo);
}

void ADZAnomalyActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 활성화된 어빌리티 정리
	if (AnomalyAbilitySystemComponent)
	{
		AnomalyAbilitySystemComponent->CancelAllAbilities();
	}
	Super::EndPlay(EndPlayReason);
}
#pragma endregion
//======================================================================================================================		
#pragma region 게터/세터

//──────────────
// 게터/세터
//──────────────	

void ADZAnomalyActorBase::SetFakeAnomalySeeInfo(const FDZFakeAnomalySeeInfo& InInfo)
{	
	if (!HasAuthority()) return; // 서버만 설정 가능
	FakeAnomalySeeInfo = InInfo;
	OnRep_FakeAnomalySeeInfo();
}

#pragma endregion
//======================================================================================================================		
#pragma region 어노말리

//──────────────
// 어노말리
//──────────────	

void ADZAnomalyActorBase::InitGAS_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !IsValid(AnomalyGameplayAbility)) return;

	// 어빌리티 부여
	FGameplayAbilitySpec AbilitySpec(AnomalyGameplayAbility, 1, INDEX_NONE,this);
	AnomalyAbilitySpecHandle = InASC->GiveAbility(AbilitySpec);
}

void ADZAnomalyActorBase::ActivateAnomaly_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !AnomalyAbilitySpecHandle.IsValid())
	{
		return;
	}
	UDZAnomalyTriggerComponent* TriggerComp = FindComponentByClass<UDZAnomalyTriggerComponent>();

	if (bActivateOnTrigger)
	{
		if (!IsValid(TriggerComp))
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s] bActivateOnTrigger == true지만 TriggerComponent 없음"), *GetName());
			return;
		}
		TriggerComp->SetupTrigger(InASC, AnomalyAbilitySpecHandle, bActivateOnTrigger, bDeactivateOnTrigger);
	}
	else
	{
		if (IsValid(TriggerComp))
		{
			TriggerComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		InASC->TryActivateAbility(AnomalyAbilitySpecHandle);
	}
}
#pragma endregion
//======================================================================================================================		
#pragma region 가짜 어노말리

//──────────────
// 가짜 어노말리
//──────────────	

void ADZAnomalyActorBase::OnRep_FakeAnomalySeeInfo()
{
	if (!IsFakeAnomaly())
	{
		return;
	}

	// 각 클라이언트가 자기 PlayerState로 독립 판단
	APlayerController* LocalPC = GetWorld()->GetFirstPlayerController();
	if (!LocalPC)
	{
		return;
	}

	APlayerState* LocalPS = LocalPC->PlayerState;
	if (!LocalPS)
	{
		return;
	}

	const bool bShouldSee = FakeAnomalySeeInfo.CanSeePlayers.Contains(LocalPS);
	
	// 가짜 액터
	GetRootComponent()->SetVisibility(bShouldSee, true);
	if (UPrimitiveComponent* Prim = GetAnomalyPrimitiveComponent())
	{
		if (bShouldSee)
			Prim->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		else
			Prim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// 원본 액터 (로컬에서만 판단)
	AActor* OriginActor = FakeAnomalySeeInfo.OriginActor;
	if (!IsValid(OriginActor)) return;

	OriginActor->SetActorHiddenInGame(bShouldSee);       // 볼 수 있으면 원본 숨김
	OriginActor->SetActorEnableCollision(!bShouldSee);   // 볼 수 있으면 원본 콜리전 끔
}
#pragma endregion
//======================================================================================================================		