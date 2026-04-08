// All CopyRight by BooZaGameStudio // 


#include "FOR_LIBRARY/LineTarce/DZLineTraceHelperLibrary.h"

EPhysicalSurface UDZLineTraceHelperLibrary::GetSurfaceTypeBelow(const UObject* WorldContextObject, const FVector& Location, float TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult)
{
	// 컨텍스트 체크
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return EPhysicalSurface::SurfaceType_Default;
	}

	// 시작 및 끝 지점
	const FVector Start = Location;
	const FVector End   = Location - FVector(0.f, 0.f, TraceDistance);
	
	// 라인 트레이스 파라미터 옵션
	InCollisionQueryParams.bReturnPhysicalMaterial = true;

	// 트레이스 실시
	World->LineTraceSingleByChannel(OutHitResult, Start, End, ECC_Visibility, InCollisionQueryParams);

	// 반환
	return GetSurfaceTypeFromHit(OutHitResult);
}


EPhysicalSurface UDZLineTraceHelperLibrary::GetSurfaceTypeFromHit(const FHitResult& Hit)
{
	if (Hit.IsValidBlockingHit() && Hit.PhysMaterial.IsValid() && IsValid(Hit.PhysMaterial.Get()))
	{
		return Hit.PhysMaterial->SurfaceType;
	}
	
	return EPhysicalSurface::SurfaceType_Default;
}
