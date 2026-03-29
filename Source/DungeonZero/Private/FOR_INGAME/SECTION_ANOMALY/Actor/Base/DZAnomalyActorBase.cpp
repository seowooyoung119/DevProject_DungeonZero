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
	
	AnomalyAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AnomalyAbilitySystemComponent"));
	AnomalyAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ADZAnomalyActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	AnomalyAbilitySystemComponent->InitAbilityActorInfo(this,this);
	
}

void ADZAnomalyActorBase::InitGAS_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !IsValid(BaseGAGEData)) return;
	for (auto& GA : BaseGAGEData->BaseGameplayAbilities)
	{
		if (!IsValid(GA)) continue;
		FGameplayAbilitySpec AbilitySpec(GA, 1, INDEX_NONE, this);
		InASC->GiveAbility(AbilitySpec);
	}
}

#pragma endregion
//======================================================================================================================		
	