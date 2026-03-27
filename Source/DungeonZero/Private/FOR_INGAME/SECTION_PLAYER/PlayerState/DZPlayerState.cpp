// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_PLAYER/PlayerState/DZPlayerState.h"
#include "AbilitySystemComponent.h"

ADZPlayerState::ADZPlayerState()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// net
	bReplicates = true;
	SetNetUpdateFrequency(100.f);
	SetMinNetUpdateFrequency(100.f);

	// gas
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
