// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player/Movement/DZGA_CharacterExhaustionWalk.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Movement/DZMovementTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Status/DZStatusTag.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UDZGA_CharacterExhaustionWalk::UDZGA_CharacterExhaustionWalk()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Movement::DZ_MOVEMENT_EXHAUSTIONWALK);
	SetAssetTags(AssetTags);
	
	// 차단된 어빌리티 태그
	BlockAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_JUMP);
	BlockAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_RUN);
	
	// 취소될 어빌리티 태그
	CancelAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_JUMP);
	CancelAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_RUN);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Movement::DZ_MOVEMENT_EXHAUSTIONWALK);
	
	// 트리커 설정
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = DZ::Status::DZ_STATUS_ZERO_STAMINA;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagAdded;

	// 트리거 추가
	AbilityTriggers.Add(TriggerData);
}

void UDZGA_CharacterExhaustionWalk::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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
	TargetCharacter->GetCharacterMovement()->MaxWalkSpeed = ExhaustionWalkSpeed;

	UE_LOG(LogTemp, Warning, TEXT("UDZGA_CharacterExhaustionWalk::ActivateAbility : %f"), TargetCharacter->GetCharacterMovement()->MaxWalkSpeed);
	UE_LOG(LogTemp, Warning, TEXT("UDZGA_CharacterExhaustionWalk::ActivateAbility : %f"), OriginalWalkSpeed);
	UE_LOG(LogTemp, Warning, TEXT("UDZGA_CharacterExhaustionWalk::ActivateAbility : %f"), ExhaustionWalkSpeed);
	
	// 타이머 설정
	if (!IsValid(GetWorld())) { K2_EndAbility(); return;}
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDZGA_CharacterExhaustionWalk::DelayForRegain, DelayTime, false);
	
}

void UDZGA_CharacterExhaustionWalk::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
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
				
				UE_LOG(LogTemp, Warning, TEXT("UDZGA_CharacterExhaustionWalk::ActivateAbility : %f"), TargetCharacter->GetCharacterMovement()->MaxWalkSpeed);
				UE_LOG(LogTemp, Warning, TEXT("UDZGA_CharacterExhaustionWalk::ActivateAbility : %f"), OriginalWalkSpeed);
				UE_LOG(LogTemp, Warning, TEXT("UDZGA_CharacterExhaustionWalk::ActivateAbility : %f"), ExhaustionWalkSpeed);
	
				// 원래 속도로 되돌리기 (다른 어빌리티에서 변경되었는지 체크)
				if (FMath::IsNearlyEqual(ExhaustionWalkSpeed, TargetCharacter->GetCharacterMovement()->MaxWalkSpeed, 1.0f))
				{
					TargetCharacter->GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
				}
			}
		}
	}
	
	// 타이머 제거
	if (IsValid(GetWorld()))
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);	
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDZGA_CharacterExhaustionWalk::DelayForRegain()
{
	K2_EndAbility();
}
