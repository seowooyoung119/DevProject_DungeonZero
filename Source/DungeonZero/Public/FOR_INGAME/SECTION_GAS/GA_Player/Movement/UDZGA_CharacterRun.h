// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "UDZGA_CharacterRun.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UUDZGA_CharacterRun : public UDZGA_BaseAbility
{
	GENERATED_BODY()

//======================================================================================================================
		
public:
	UUDZGA_CharacterRun();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
//======================================================================================================================
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDZGA_CharacterRun")
	float RunSpeed = 500.0f;

	UPROPERTY()
	float OriginalWalkSpeed = 0.0f;
	
		
//======================================================================================================================
	
	// 지구력 어트리뷰트 변경 시 호출될 콜백
	void OnStaminaChanged(const FOnAttributeChangeData& Data);

	// 어트리뷰트 델리게이트 핸들
	FDelegateHandle StaminaChangedDelegateHandle;

//======================================================================================================================
	
};
