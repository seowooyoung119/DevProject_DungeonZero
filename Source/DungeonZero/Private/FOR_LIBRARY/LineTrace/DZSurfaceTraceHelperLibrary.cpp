// All CopyRight by BooZaGameStudio // 


#include "FOR_LIBRARY/LineTarce/DZSurfaceTraceHelperLibrary.h"

EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeInDirection(const UObject* WorldContextObject, const FVector& Location, const FVector& Direction, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult)
{
	// 컨텍스트 체크
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return EPhysicalSurface::SurfaceType_Default;
	}
	
	// 시작 및 끝 지점
	const FVector Start = Location;
	const FVector End   = Location + (Direction.GetSafeNormal() * TraceDistance);
    
	// 라인 트레이스 파라미터 옵션
	InCollisionQueryParams.bReturnPhysicalMaterial = true;

	// 트레이스 실시
	World->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, InCollisionQueryParams);

	// 표면 타입 반환
	return GetSurfaceTypeFromHit(OutHitResult);
}

EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeAbove(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams&InCollisionQueryParams, FHitResult& OutHitResult)
{
	return GetSurfaceTypeInDirection(WorldContextObject, Location, FVector::UpVector, TraceDistance, InCollisionQueryParams, OutHitResult);
}

EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeBelow(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult)
{
	return GetSurfaceTypeInDirection(WorldContextObject, Location, FVector::DownVector, TraceDistance, InCollisionQueryParams, OutHitResult);
}
EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeForward(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult)
{
	return GetSurfaceTypeInDirection(WorldContextObject, Location, FVector::ForwardVector, TraceDistance, InCollisionQueryParams, OutHitResult);
}

EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeBackward(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult)
{
	return GetSurfaceTypeInDirection(WorldContextObject, Location, FVector::BackwardVector, TraceDistance, InCollisionQueryParams, OutHitResult);
}

EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeRight(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult)
{
	return GetSurfaceTypeInDirection(WorldContextObject, Location, FVector::RightVector, TraceDistance, InCollisionQueryParams, OutHitResult);
}

EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeLeft(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult)
{
	return GetSurfaceTypeInDirection(WorldContextObject, Location, FVector::LeftVector, TraceDistance, InCollisionQueryParams, OutHitResult);
}

EPhysicalSurface UDZSurfaceTraceHelperLibrary::GetSurfaceTypeFromHit(const FHitResult& Hit)
{
	if (Hit.IsValidBlockingHit() && Hit.PhysMaterial.IsValid() && IsValid(Hit.PhysMaterial.Get()))
	{
		return Hit.PhysMaterial->SurfaceType;
	}
	
	return EPhysicalSurface::SurfaceType_Default;
}
