// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player//Status/UDZGA_HandleStamina.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Movement/DZMovementTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Init/DZInitTag.h"
#include "FOR_INGAME/SECTION_GAS/AttributeSet/DZAttributeSet.h"
#include "AbilitySystemComponent.h"

UUDZGA_HandleStamina::UUDZGA_HandleStamina()
{
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Status::DZ_STATUS_STAMINA);
	AssetTags.AddTag(DZ::GA::DZ_GA_INIT);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Status::DZ_STATUS_STAMINA);
	
	// 규칙
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UUDZGA_HandleStamina::ActivateAbility(const FGameplayAbilitySpecHandle Handle,const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// 감소 스태미나 ge 적용 
	if (IsValid(ReduceStaminaConsumptionEffectClass))
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(ReduceStaminaConsumptionEffectClass);
		ReduceStaminaEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
	
	// 회복 스태미나 ge 적용
	if (IsValid(RegainStaminaConsumptionEffectClass))
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(RegainStaminaConsumptionEffectClass);
		ReduceStaminaEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
	
	// 스태미나 어트리뷰트 변화 구독 
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (IsValid(ASC)) StaminaChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(UDZAttributeSet::GetStaminaAttribute()).AddUObject(this, &UUDZGA_HandleStamina::OnStaminaChanged);
}

void UUDZGA_HandleStamina::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(ASC)) return;

	// 스태미나가 일정 수치 미만이면 지구력 로우 태그 부여
	if (Data.NewValue <= LowStaminaThreshold)
	{
		// 중복 방지 (부여가 되지 않았을 때만 부여)
		if (!ASC->HasMatchingGameplayTag(LowStaminaTag)) ASC->AddLooseGameplayTag(LowStaminaTag);
		
		// 0 일 경우 제로 스태미나 태그 적용 
		if (Data.NewValue <= 0)
		{
			if (!ASC->HasMatchingGameplayTag(ZeroStaminaTag)) ASC->AddLooseGameplayTag(ZeroStaminaTag);
		};
		
		// 0 이 아닐 경우 제로 스태미나 빼기
		if (Data.NewValue > 0)
		{
			if (ASC->HasMatchingGameplayTag(ZeroStaminaTag)) ASC->RemoveLooseGameplayTag(ZeroStaminaTag);
		}
		
		return;
	}

	// 스태미나가 일정 수치 이상일 때 지구력 로우 태그 해제
	if (Data.NewValue > RecoverThreshold)
	{
		// 중복 방지 (부여가 되어 있을 때만 제거)
		if (ASC->HasMatchingGameplayTag(LowStaminaTag)) ASC->RemoveLooseGameplayTag(LowStaminaTag);
	}
}
