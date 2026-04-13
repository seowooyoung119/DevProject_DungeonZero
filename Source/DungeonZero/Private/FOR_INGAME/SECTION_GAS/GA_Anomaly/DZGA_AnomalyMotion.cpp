// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyMotion.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "FOR_COMMON/SECTION_TAG/GAS/GA/DZGATag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/DZGameplayCueTag.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"

UDZGA_AnomalyMotion::UDZGA_AnomalyMotion()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::GA::DZ_GA_ANOMALY_MOTION);
	SetAssetTags(AssetTags);

	// 어빌리티 트리거 태그
	bRetriggerInstancedAbility = true;
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = DZ::GA::DZ_GA_ANOMALY_EVENTTRIGGER;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(TriggerData);
}

void UDZGA_AnomalyMotion::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	if (!HasAuthority(&ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(ASC))
	{
		return;			
	}
	// 모션 큐 실행
	ASC->AddGameplayCue(DZ::GameplayCue::DZ_CUE_ANOMALY_MOTION);
}

void UDZGA_AnomalyMotion::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	if (HasAuthority(&ActivationInfo))
	{
		// 큐 종료
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		if (ASC)
		{
			ASC->RemoveGameplayCue(DZ::GameplayCue::DZ_CUE_ANOMALY_MOTION);
		}
		// 어노말리 종료 함수 실행
		ADZAnomalyActorBase* AnomalyActor = Cast<ADZAnomalyActorBase>(GetAvatarActorFromActorInfo());
		if (IsValid(AnomalyActor))
		{
			AnomalyActor->AnomalySealAdditionalFunction_Implementation();
		}
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
