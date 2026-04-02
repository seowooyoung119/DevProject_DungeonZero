// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/Comp/DZSoundComponent.h"
#include "Kismet/GameplayStatics.h"


UDZSoundComponent::UDZSoundComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

EPhysicalSurface UDZSoundComponent::GetSurfaceTypeBelow(const FVector& Location, float TraceLength) const
{
	// 아래 방향 표면 타입 검출
	FHitResult HitResult;
	FVector Start = Location;
	FVector End = Location - FVector(0.f, 0.f, TraceLength);

	if (LineTrace(Start, End, HitResult))
	{
		if (HitResult.PhysMaterial.IsValid())
		{
			return HitResult.PhysMaterial->SurfaceType;
		}
	}
	return EPhysicalSurface::SurfaceType_Default;
}

EPhysicalSurface UDZSoundComponent::GetSurfaceTypeFront(const FVector& Location, const FVector& ForwardVector,
                                                      float TraceLength) const
{
	// 앞 방향 표면 타입 검출
	FHitResult HitResult;
	FVector Start = Location;
	FVector End = Location + ForwardVector * TraceLength;

	if (LineTrace(Start, End, HitResult))
	{
		if (HitResult.PhysMaterial.IsValid())
		{
			return HitResult.PhysMaterial->SurfaceType;
		}
	}
	return EPhysicalSurface::SurfaceType_Default;
}

EPhysicalSurface UDZSoundComponent::GetSurfaceTypeFromHit(const FHitResult& Hit) const
{
	// HitResult 표면 타입 검출
	FHitResult HitResult;
	FVector Start = Hit.ImpactPoint + Hit.ImpactNormal * 10.f;
	FVector End = Hit.ImpactPoint - Hit.ImpactNormal * 10.f;

	if (LineTrace(Start, End, HitResult))
	{
		if (HitResult.PhysMaterial.IsValid())
		{
			return HitResult.PhysMaterial->SurfaceType;
		}
	}
	return EPhysicalSurface::SurfaceType_Default;
}

bool UDZSoundComponent::LineTrace(const FVector& Start, const FVector& End, FHitResult& OutHit) const
{
	// 표면 타입 검출을 위한 라인트레이스
	FCollisionQueryParams Params;
	Params.bReturnPhysicalMaterial = true;

	return GetWorld()->LineTraceSingleByChannel(
		OutHit,
		Start,
		End,
		ECC_Visibility,
		Params);
}

void UDZSoundComponent::PlaySoundAtLocation(USoundBase* Sound, const FVector& Location) const
{
	// 사운드 재생
	if (Sound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location,
		                                      FRotator::ZeroRotator,
		                                      1.f, 1.f, 0.f,
		                                      DefaultAttenuation);
	}
}

