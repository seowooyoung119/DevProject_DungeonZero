// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_GAS/GA/Movement/DZGA_CharacterJump.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_ROLE/Job/DZJobRoleInterface.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_TAG/GAS/Movement/DZMovementTag.h"
#include "GameFramework/Character.h"

UDZGA_CharacterJump::UDZGA_CharacterJump()
{
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Movement::DZ_MOVEMENT_JUMP);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Movement::DZ_MOVEMENT_JUMP);
	
	// 규칙
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UDZGA_CharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	// 시전자 체크
	if (!IsValid(GetAvatarActorFromActorInfo())) { K2_EndAbility(); return;}

	// 타겟 체크 
	ACharacter* TargetCharacter = CastChecked<ACharacter>(GetAvatarActorFromActorInfo());
	if (!IsValid(TargetCharacter)) { K2_EndAbility(); return; }
	
	// 인터페이스 체크 
	IDZJobRoleInterface* JobInterface = Cast<IDZJobRoleInterface>(GetAvatarActorFromActorInfo());
	if (!JobInterface) { K2_EndAbility(); return; }
	
	// 직업 가져오기
	FGameplayTag CurrentJobTag = IDZJobRoleInterface::Execute_GetJobRoleTag(GetAvatarActorFromActorInfo());
	
	// 직업 일치시 점프 후 종료
	if (CurrentJobTag == JumpJobRoleTag) TargetCharacter->Jump();
	K2_EndAbility();
}
