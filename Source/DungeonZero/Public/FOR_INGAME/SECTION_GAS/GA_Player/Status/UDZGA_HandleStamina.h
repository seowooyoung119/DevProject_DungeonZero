// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Status/DZStatusTag.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "UDZGA_HandleStamina.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UUDZGA_HandleStamina : public UDZGA_BaseAbility
{
	GENERATED_BODY()
	
//======================================================================================================================
	
public:
	UUDZGA_HandleStamina();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

//======================================================================================================================
	
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "DZ")
	TSubclassOf<UGameplayEffect> ReduceStaminaConsumptionEffectClass = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "DZ")
	TSubclassOf<UGameplayEffect> RegainStaminaConsumptionEffectClass = nullptr;
	
	// 현재 적용된 이펙트를 나중에 제거하기 위해 핸들 저장
	FActiveGameplayEffectHandle ReduceStaminaEffectHandle;

//======================================================================================================================
	
	// 지구력 어트리뷰트 변경 시 호출될 콜백
	void OnStaminaChanged(const FOnAttributeChangeData& Data);

	// 어트리뷰트 델리게이트 핸들
	FDelegateHandle StaminaChangedDelegateHandle;

	// 스태미나 로우 태그를 적용하기 위한 수치
	UPROPERTY(EditDefaultsOnly, Category = "DZ")
	float LowStaminaThreshold = 10.f;
	
	// 다시 회복하기 위한 시점까지 적용 수치
	UPROPERTY(EditDefaultsOnly, Category = "DZ")
	float RecoverThreshold = 30.f;
	
	// 스태미나 일정 수치 미만 시 적용할 태그
	UPROPERTY(EditDefaultsOnly, Category = "DZ")
	FGameplayTag LowStaminaTag = DZ::Status::DZ_STATUS_LOW_STAMINA;	
	
	// 스태미나 0일 경우 태그 
	UPROPERTY(EditDefaultsOnly, Category = "DZ")
	FGameplayTag ZeroStaminaTag = DZ::Status::DZ_STATUS_ZERO_STAMINA;
	
//======================================================================================================================
	
};
