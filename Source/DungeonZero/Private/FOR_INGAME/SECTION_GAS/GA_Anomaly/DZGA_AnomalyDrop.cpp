// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyDrop.h"

#include "FOR_COMMON/SECTION_TAG/GAS/GA/DZGATag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Status/DZAnomalyStatus.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "FOR_INGAME/SECTION_ANOMALY/Comp/DZAnomalyPhysicsImpactComponent.h"
//======================================================================================================================	
#pragma region 라이프_사이클

//━━━━━━━━━━━━━━━━━━━━
// 라이프 사이클
//━━━━━━━━━━━━━━━━━━━━	
UDZGA_AnomalyDrop::UDZGA_AnomalyDrop()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::GA::DZ_GA_ANOMALY_DROP);
	SetAssetTags(AssetTags);
	// // 차단 태그
	// ActivationBlockedTags.AddTag(DZ::AnomalyStatus::DZ_ANOMALYSTATUS_PHYSICSIMPACTEND);
	
	// 어빌리티 트리거 태그
	bRetriggerInstancedAbility = true;
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = DZ::GA::DZ_GA_ANOMALY_EVENTTRIGGER;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(TriggerData);
}

void UDZGA_AnomalyDrop::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo,
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

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!IsValid(AvatarActor))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	UDZAnomalyPhysicsImpactComponent* PhysicsImpactComponent = AvatarActor->FindComponentByClass<
		UDZAnomalyPhysicsImpactComponent>();
	if (!IsValid(PhysicsImpactComponent))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	// 피직스 활성화 및 Hit 이벤트 바인딩
	PhysicsImpactComponent->ActivatePhysics_internal(AbilityTags);
	// 랜덤 임펄스
	if (!CachedPrimitive)
	{
		CachedPrimitive = PhysicsImpactComponent->GetOwnerPrimitiveComponent();
	}
	Launch(TriggerEventData->Instigator, AvatarActor);
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UDZGA_AnomalyDrop::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                   bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDZGA_AnomalyDrop::Launch(const AActor* Instigator, const AActor* AvatarActor) const
{
	// 1. 기본 방향 설정 (액터의 앞방향과 윗방향)
	FVector Forward = AvatarActor->GetActorForwardVector();
	FVector Up = AvatarActor->GetActorUpVector();

	// 2. 랜덤성 추가
	FVector RandomDir = FMath::VRandCone(Forward, FMath::DegreesToRadians(70.0f));

	// 3. 위쪽 방향 힘 강화
	FVector LaunchDir = (RandomDir + (Up * 2.0f)).GetSafeNormal();
	
	CachedPrimitive->AddImpulse(LaunchDir * ImpulseStrength, NAME_None, true);
}
#pragma endregion
//======================================================================================================================	
