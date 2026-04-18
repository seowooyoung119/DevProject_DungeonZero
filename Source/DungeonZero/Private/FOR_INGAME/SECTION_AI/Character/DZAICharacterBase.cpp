// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/Character/DZAICharacterBase.h"
#include "FOR_INGAME/SECTION_GAS/AttributeSet/DZAttributeSet.h"
#include "FOR_INGAME/SECTION_GAS/Data/Asset/DZGiveGAGEDataAsset.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Init/DZInitTag.h"


//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZAICharacterBase::ADZAICharacterBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// net
	bReplicates = true;
	SetReplicatingMovement(true);

	// asc
	AttributeSet = CreateDefaultSubobject<UDZAttributeSet>(TEXT("AttributeSet"));
	
	// gas
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ADZAICharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// GA 초기화 
	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	// GA 부여
	if (HasAuthority())
	{
		InitGAS_internal(AbilitySystemComponent);
	}
}

#pragma endregion
//======================================================================================================================	
#pragma region GAS
	//━━━━━━━━━━━━━━━━━━━━
	// GAS
	//━━━━━━━━━━━━━━━━━━━━

void ADZAICharacterBase::InitGAS_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !IsValid(BaseGAGEData))
	{
		return;
	}
	
	for (auto& GA : BaseGAGEData->BaseGameplayAbilities)
	{
		if (!IsValid(GA))
		{
			continue;
		}
		
		FGameplayAbilitySpec AbilitySpec(GA, 1, INDEX_NONE, this);
		auto Handle = InASC->GiveAbility(AbilitySpec);
		
		UGameplayAbility* AbilityCDO = GA.GetDefaultObject();
		if (!IsValid(AbilityCDO))
		{
			continue;
		}
		
		if (AbilityCDO->GetAssetTags().HasTag(DZ::GA::DZ_GA_INIT))
		{
			InASC->TryActivateAbility(Handle);
		}
	}
}


#pragma endregion
//======================================================================================================================	