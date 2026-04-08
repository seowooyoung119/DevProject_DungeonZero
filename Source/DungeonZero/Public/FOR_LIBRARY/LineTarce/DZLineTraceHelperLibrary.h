// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZLineTraceHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZLineTraceHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** 월드 좌표 기준으로 아래 방향 라인 트레이스 후 표면 타입 반환 */
	static EPhysicalSurface GetSurfaceTypeBelow(const UObject* WorldContextObject, const FVector& Location, float TraceDistance, FCollisionQueryParams& InCollisionQueryParams, FHitResult& OutHitResult);
	
	/** HitResult에서 표면 타입 반환 */
	static EPhysicalSurface GetSurfaceTypeFromHit(const FHitResult& Hit);
	
};
