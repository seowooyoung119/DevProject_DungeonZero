// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "AbilitySystemComponent.h"
#include "FOR_INGAME/SECTION_GAS/Data/Asset/DZGiveGAGEDataAsset.h"
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

	if (!HasAuthority() || !IsValid(BaseGAGEData))
	{
		return;
	}

	InitGAS_internal(AnomalyAbilitySystemComponent);
	ActivateAnomaly_internal(AnomalyAbilitySystemComponent);
}

#pragma endregion
//======================================================================================================================		
#pragma region 어노말리

//──────────────
// 어노말리
//──────────────	

void ADZAnomalyActorBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZAnomalyActorBase, ReplicatedAnomalyScale);
}

void ADZAnomalyActorBase::SetAnomalyScale(float InScale)
{
	ReplicatedAnomalyScale = InScale;
	SetActorScale3D(FVector(InScale));
}

void ADZAnomalyActorBase::InitGAS_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !IsValid(BaseGAGEData)) return;

	// 랜덤한 하나의 어빌리티만 부여
	// 유효한 어빌리티로 배열 생성
	TArray<TSubclassOf<UGameplayAbility>> ValidAbilities;
	for (auto& GA : BaseGAGEData->BaseGameplayAbilities)
	{
		if (!IsValid(GA)) continue;
		ValidAbilities.Add(GA);
	}
	FGameplayAbilitySpec AbilitySpec(ValidAbilities[FMath::RandRange(0, ValidAbilities.Num() - 1)], 1, INDEX_NONE,
	                                 this);
	AnomalyAbilitySpecHandle = 	InASC->GiveAbility(AbilitySpec);
}

void ADZAnomalyActorBase::ActivateAnomaly_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !AnomalyAbilitySpecHandle.IsValid())
	{
		return;
	}
	InASC->TryActivateAbility(AnomalyAbilitySpecHandle);
}

void ADZAnomalyActorBase::OnRep_AnomalyScale()
{
	SetActorScale3D(FVector(ReplicatedAnomalyScale));
}

#pragma endregion
//======================================================================================================================		
