// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Player/DZGCN_PlayerDead.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"


ADZGCN_PlayerDead::ADZGCN_PlayerDead()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ADZGCN_PlayerDead::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnActive_Implementation(MyTarget, Parameters);
	
	if (ACharacter* Character = Cast<ACharacter>(MyTarget); IsValid(Character))
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
	
	return true;
}

bool ADZGCN_PlayerDead::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnRemove_Implementation(MyTarget, Parameters);
	
	if (ACharacter* Character = Cast<ACharacter>(MyTarget); IsValid(Character))
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
	
	return true;
}
