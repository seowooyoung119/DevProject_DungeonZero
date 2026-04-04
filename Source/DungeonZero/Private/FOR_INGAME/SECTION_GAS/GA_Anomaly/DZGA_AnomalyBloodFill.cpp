// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyBloodFill.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GA/DZGATag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/DZGameplayCueTag.h"

UDZGA_AnomalyBloodFill::UDZGA_AnomalyBloodFill()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::GA::DZ_GA_ANOMALY_BLOODFILL);
	SetAssetTags(AssetTags);
}

void UDZGA_AnomalyBloodFill::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!HasAuthority(&ActivationInfo))
	{
		return;
	}
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(ASC))
	{
		return;			
	}
	FGameplayCueParameters CueParams;
	CueParams.AggregatedSourceTags.AppendTags(AbilityTags);
	// 데칼 부착 큐 실행
	ASC->AddGameplayCue(DZ::GameplayCue::DZ_CUE_ANOMALY_DECAL, CueParams);
	// 머티리얼 변경 큐 실행
	ASC->AddGameplayCue(DZ::GameplayCue::DZ_CUE_ANOMALY_MATERIAL, CueParams);
}

void UDZGA_AnomalyBloodFill::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (HasAuthority(&ActivationInfo))
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		if (ASC)
		{
			ASC->RemoveGameplayCue(DZ::GameplayCue::DZ_CUE_ANOMALY_DECAL);
			ASC->RemoveGameplayCue(DZ::GameplayCue::DZ_CUE_ANOMALY_MATERIAL);
		}
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}