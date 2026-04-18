// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "DZGA_PlayerDead.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_PlayerDead : public UDZGA_BaseAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_PlayerDead();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	
	// 죽었을 때 발생시킬 게임플레이 큐 태그
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FGameplayTag PlayerDeadTag = FGameplayTag::EmptyTag;
};
