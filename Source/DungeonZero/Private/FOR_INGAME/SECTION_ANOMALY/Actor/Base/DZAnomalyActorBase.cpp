// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "AbilitySystemComponent.h"
#include "FOR_INGAME/SECTION_GAS/Data/Asset/DZGiveGAGEDataAsset.h"


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

void ADZAnomalyActorBase::InitGAS_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !IsValid(BaseGAGEData)) return;
	/* 모든 어빌리티 부여
	 *for (auto& GA : BaseGAGEData->BaseGameplayAbilities)
	{
		if (!IsValid(GA)) continue;
		FGameplayAbilitySpec AbilitySpec(GA, 1, INDEX_NONE, this);
		InASC->GiveAbility(AbilitySpec);
	}*/
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

#pragma endregion
//======================================================================================================================		
