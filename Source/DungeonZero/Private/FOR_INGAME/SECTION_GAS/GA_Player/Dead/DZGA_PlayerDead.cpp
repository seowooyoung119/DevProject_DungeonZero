// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Player/Dead/DZGA_PlayerDead.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Interact/DZInteractTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Movement/DZMovementTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/RightClick/DZRightClickTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Dead/DZDeadTag.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZGameModeMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "GameFramework/GameplayMessageSubsystem.h"

UDZGA_PlayerDead::UDZGA_PlayerDead()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Dead::DZ_DEAD_PLAYER);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Dead::DZ_DEAD_PLAYER);
	
	// 모든 움직임 취소
	CancelAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_JUMP);
	CancelAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_RUN);
	CancelAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_EXHAUSTIONWALK);
	
	// 모든 움직임 차단
	BlockAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_JUMP);
	BlockAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_RUN);
	BlockAbilitiesWithTag.AddTag(DZ::Movement::DZ_MOVEMENT_EXHAUSTIONWALK);
	
	// 우클릭 취소
	CancelAbilitiesWithTag.AddTag(DZ::RightClick::DZ_RIGHTCLICK_USEITEM);
	
	// 우클릭 차단
	BlockAbilitiesWithTag.AddTag(DZ::RightClick::DZ_RIGHTCLICK_USEITEM);
	
	// 특수 상호작용 취소
	CancelAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_SPECIALINTERACT);
	
	// 특수 상호작용 차단
	BlockAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_SPECIALINTERACT);
	
	// 아이템 줍기, 쓰기, 버리기 취소
	CancelAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_PICKUPITEM);
	CancelAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_USEITEM);
	CancelAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_DROPITEM);
	
	// 아이템 줍기, 쓰기, 버리기 차단
	BlockAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_PICKUPITEM);
	BlockAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_USEITEM);
	BlockAbilitiesWithTag.AddTag(DZ::Interact::DZ_INTERACT_DROPITEM);
	
}

void UDZGA_PlayerDead::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get()); IsValid(Character))
	{
		// 1. 캡슐 컴포넌트 설정: 캐릭터/AI 충돌만 무시
		if (UCapsuleComponent* Capsule = Character->GetCapsuleComponent(); IsValid(Capsule))
		{
			Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		}

		// 2. 메쉬 컴포넌트 설정: 메쉬가 콜리전을 가지고 있는 경우를 위해 처리
		if (USkeletalMeshComponent* Mesh = Character->GetMesh(); IsValid(Mesh))
		{
			Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
            
		}
	}
	
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (IsValid(ASC) && PlayerDeadTag.IsValid())
	{
		// 큐 파라미터 정보
		FGameplayCueParameters CueParams;
		CueParams.TargetAttachComponent = GetAvatarActorFromActorInfo()->GetRootComponent();
		CueParams.Instigator = GetAvatarActorFromActorInfo();
		CueParams.EffectCauser = GetAvatarActorFromActorInfo();
		CueParams.AbilityLevel = GetAbilityLevel();
	
		// 게임 플레이 큐 요청
		ASC->AddGameplayCue(PlayerDeadTag, CueParams);
	}
	
	// 죽음 알림 (메세지 호출)
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZGameModeDeathCountMSG Payload;
	MessageSubsystem.BroadcastMessage(DZ::GameModeMSG::DZ_GAMEMODE_DEADCOUNT, Payload);
	
}

void UDZGA_PlayerDead::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get()); IsValid(Character))
	{
		// 1. 캡슐 컴포넌트 원복
		if (UCapsuleComponent* Capsule = Character->GetCapsuleComponent(); IsValid(Capsule))
		{
			Capsule->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		}

		// 2. 메쉬 컴포넌트 원복
		if (USkeletalMeshComponent* Mesh = Character->GetMesh(); IsValid(Mesh))
		{
			Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		}
	}
	
	// ASC, 게임 플레이 큐 태그 체크
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (IsValid(ASC) && PlayerDeadTag.IsValid())
	{
		// 게임 플레이 큐 요청
		ASC->RemoveGameplayCue(PlayerDeadTag);
	}
	
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
