// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Anomaly/DZGA_AnomalyJump.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GA/DZGATag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Status/DZAnomalyStatus.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "FOR_INGAME/SECTION_ANOMALY/Comp/DZAnomalyPhysicsImpactComponent.h"
//======================================================================================================================	
#pragma region 라이프_사이클

//━━━━━━━━━━━━━━━━━━━━
// 라이프 사이클
//━━━━━━━━━━━━━━━━━━━━	
UDZGA_AnomalyJump::UDZGA_AnomalyJump()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::GA::DZ_GA_ANOMALY_JUMP);
	SetAssetTags(AssetTags);

	// 어빌리티 트리거 태그
	bRetriggerInstancedAbility = true;
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = DZ::GA::DZ_GA_ANOMALY_EVENTTRIGGER;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(TriggerData);
}

void UDZGA_AnomalyJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
	// Launch 바인딩
	if (!CachedPrimitive)
	{
		CachedPrimitive = PhysicsImpactComponent->GetOwnerPrimitiveComponent();
	}
	if (CachedPrimitive->OnComponentHit.IsAlreadyBound(this, &UDZGA_AnomalyJump::OnHitRelaunch))
	{
		return;
	}
	// Hit 이벤트 바인딩
	CachedPrimitive->OnComponentHit.AddDynamic(this, &UDZGA_AnomalyJump::OnHitRelaunch);
	// 랜덤 임펄스
	Launch(TriggerEventData->Instigator, AvatarActor);
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(ASC))
	{
		return;			
	}

	// 루프 사운드 큐 실행
	ASC->AddGameplayCue(LoopSoundCueTag);
}

void UDZGA_AnomalyJump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                                   bool bWasCancelled)
{
	if (HasAuthority(&ActivationInfo))
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
		if (ASC)
		{
			ASC->RemoveGameplayCue(LoopSoundCueTag);
		}
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDZGA_AnomalyJump::OnHitRelaunch(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                      FVector NormalImpulse, const FHitResult& Hit)
{
	// 바닥 충돌일 때만 (Normal이 위를 향할 때)
	if (Hit.Normal.Z < 0.7f)
	{
		return;
	}
	Launch(CachedInstigator, OtherActor);
}

void UDZGA_AnomalyJump::Launch(const AActor* Instigator, const AActor* AvatarActor) const
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
