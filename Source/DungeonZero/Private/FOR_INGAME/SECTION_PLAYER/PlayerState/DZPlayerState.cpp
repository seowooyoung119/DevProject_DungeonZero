// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_PLAYER/PlayerState/DZPlayerState.h"
#include "AbilitySystemComponent.h"
#include "FOR_INGAME/SECTION_GAS/AttributeSet/DZAttributeSet.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZPlayerState::ADZPlayerState()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// net
	bReplicates = true;
	SetNetUpdateFrequency(100.f);
	SetMinNetUpdateFrequency(100.f);

	// asc
	AttributeSet = CreateDefaultSubobject<UDZAttributeSet>(TEXT("AttributeSet"));
	
	// gas
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
}

#pragma endregion
//======================================================================================================================	