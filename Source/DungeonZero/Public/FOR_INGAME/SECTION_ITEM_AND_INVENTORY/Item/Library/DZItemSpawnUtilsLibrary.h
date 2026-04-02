// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZItemSpawnUtilsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZItemSpawnUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** NavMesh를 사용하여 가장 가까운 안전한 바닥 위치를 반환 */
	static bool GetSafeLocationOnNavMesh(const UObject* WorldContextObject, const FVector& InLocation, FVector& OutResultLocation, const float& SearchRadius);

	/** NavMesh를 사용하여 가장 가까운 안전한 바닥 위치를 반환 - 최소 최대 거리로 도넛 모양 반경에서 검색 */
	static bool GetSafeLocationOnNavMeshInRing(const UObject* WorldContextObject, const FVector& InLocation, FVector& OutResultLocation, const float& MinRadius, const float& MaxRadius, const int32& MaxRetries);
};
