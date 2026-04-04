// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player//Movement/UDZGA_CharacterRun.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Movement/DZMovementTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Status/DZStatusTag.h"
#include "FOR_INGAME/SECTION_GAS/AttributeSet/DZAttributeSet.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UUDZGA_CharacterRun::UUDZGA_CharacterRun()
{
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Movement::DZ_MOVEMENT_RUN);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Movement::DZ_MOVEMENT_RUN);
	
	// 발동 차단 태그
	ActivationBlockedTags.AddTag(DZ::Status::DZ_STATUS_LOW_STAMINA);	// 지구력 낮음
	
	// 규칙
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UUDZGA_CharacterRun::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// 시전자 체크
	if (!IsValid(GetAvatarActorFromActorInfo())) { K2_EndAbility(); return;}

	// 타겟 체크 
	ACharacter* TargetCharacter = CastChecked<ACharacter>(GetAvatarActorFromActorInfo());
	if (!IsValid(TargetCharacter)) { K2_EndAbility(); return; }

	// AMC 체크
	if (!IsValid(TargetCharacter->GetCharacterMovement()))  { K2_EndAbility(); return; }
	
	// 기존 속도 캐싱
	OriginalWalkSpeed = TargetCharacter->GetCharacterMovement()->MaxWalkSpeed;
	
	// 속도 변경
	TargetCharacter->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	
	
	// 스태미나 어트리뷰트 변화 구독 
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (IsValid(ASC)) StaminaChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(UDZAttributeSet::GetStaminaAttribute()).AddUObject(this, &UUDZGA_CharacterRun::OnStaminaChanged);
}

void UUDZGA_CharacterRun::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// 시전자 체크
	if (IsValid(GetAvatarActorFromActorInfo()))
	{
		// 타겟 체크 
		ACharacter* TargetCharacter = CastChecked<ACharacter>(GetAvatarActorFromActorInfo());
		if (IsValid(TargetCharacter))
		{
			// AMC 체크
			if (IsValid(TargetCharacter->GetCharacterMovement()))
			{
				// 원래 속도로 되돌리기 (다른 어빌리티에서 변경되었는지 체크)
				if (FMath::IsNearlyEqual(RunSpeed, TargetCharacter->GetCharacterMovement()->MaxWalkSpeed, 1.0f))
				{
					TargetCharacter->GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
				}
			}
		}
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UUDZGA_CharacterRun::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	if (Data.NewValue <= 0.0f) K2_EndAbility();
}
