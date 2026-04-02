// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/Comp/DZFootstepSoundComponent.h"

#include "GameFramework/Character.h"


UDZFootstepSoundComponent::UDZFootstepSoundComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDZFootstepSoundComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = CastChecked<ACharacter>(GetOwner());
	OwnerCharacter->LandedDelegate.AddDynamic(this, &UDZFootstepSoundComponent::OnLanded);
}

void UDZFootstepSoundComponent::PlayFootstepSound(const FVector& Location, const bool bIsLeft)
{
	// 표면 타입 검출
	EPhysicalSurface SurfaceType = GetSurfaceTypeBelow(Location, 50.f);

	// 타입에 매핑된 사운드 출력
	const auto* Sounds = FootstepSounds.Find(SurfaceType);
	if (!Sounds)
	{
		// 매핑된 사운드 없으면 디폴트 사운드
		Sounds = &DefaultFootstepSound;
	}
	USoundBase* Sound = Sounds->FootStep_Right;

	if (bIsLeft)
	{
		Sound = Sounds->FootStep_Left;
	}

	PlaySoundAtLocation(Sound, Location);
}

void UDZFootstepSoundComponent::OnLanded(const FHitResult& Hit)
{
	// 표면 타입 검출
	if (!Hit.IsValidBlockingHit())
	{
		return;
	}
	EPhysicalSurface SurfaceType = GetSurfaceTypeFromHit(Hit);
	
	// 타입에 매핑된 사운드 출력
	const auto* Sounds = FootstepSounds.Find(SurfaceType);
	if (!Sounds)
	{
		// 매핑된 사운드 없으면 디폴트 사운드
		Sounds = &DefaultFootstepSound;
	}

	PlaySoundAtLocation(Sounds->FootStep_Left, Hit.ImpactPoint);
	PlaySoundAtLocation(Sounds->FootStep_Right, Hit.ImpactPoint);
}

