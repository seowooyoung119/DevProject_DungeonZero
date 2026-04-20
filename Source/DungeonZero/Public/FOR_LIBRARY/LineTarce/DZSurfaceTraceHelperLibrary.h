// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZSurfaceTraceHelperLibrary.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONZERO_API UDZSurfaceTraceHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	/** 특정 위치에서 지정한 방향으로 라인 트레이스 후 표면 타입 반환 (핵심 로직) */
    static EPhysicalSurface GetSurfaceTypeInDirection(const UObject* WorldContextObject, const FVector& Location, const FVector& Direction, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);

	//-------------------
    /** 방향별 편의 함수들 */
	/** 위(Up) 방향 표면 타입 반환 */
    static EPhysicalSurface GetSurfaceTypeAbove(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);
	/** 아래(Down) 방향 표면 타입 반환 */
    static EPhysicalSurface GetSurfaceTypeBelow(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);
	/** 앞(Forward) 방향 표면 타입 반환 */
    static EPhysicalSurface GetSurfaceTypeForward(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);
	/** 뒤(Backward) 방향 표면 타입 반환 */
    static EPhysicalSurface GetSurfaceTypeBackward(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);
	/** 오른쪽(Right) 방향 표면 타입 반환 */
    static EPhysicalSurface GetSurfaceTypeRight(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);
	/** 왼쪽(Left) 방향 표면 타입 반환 */
    static EPhysicalSurface GetSurfaceTypeLeft(const UObject* WorldContextObject, const FVector& Location, const float& TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);
	/** 방향별 편의 함수들 */
	//-------------------
	
	/** HitResult에서 표면 타입 반환 */
	static EPhysicalSurface GetSurfaceTypeFromHit(const FHitResult& Hit);
	
};
