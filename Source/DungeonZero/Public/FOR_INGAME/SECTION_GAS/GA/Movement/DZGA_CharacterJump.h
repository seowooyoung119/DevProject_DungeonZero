// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_ROLE/Job/DZJobRoleTag.h"
#include "DZGA_CharacterJump.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_CharacterJump : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_CharacterJump();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	// 점프가 가능하기 위해서 확인해야하는 직업 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ")
	FGameplayTag JumpJobRoleTag = DZ::JobRole::DS_JOBROLE_ARCHER;
	
};
