// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DZGA_ActiveToggleHotkeyBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_ActiveToggleHotkeyBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_ActiveToggleHotkeyBase();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	
	// 실제 핫키 숫자가 아니라 -1 해서 배열과 매칭해야함. 주의.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZGA_ActiveToggleHotkeyBase")
	int32 TargetHotKeyIndex = -1;
	
};
