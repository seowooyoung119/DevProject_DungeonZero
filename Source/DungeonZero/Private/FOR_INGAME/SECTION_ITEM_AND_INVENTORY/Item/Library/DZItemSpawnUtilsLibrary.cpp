// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemSpawnUtilsLibrary.h"
#include "NavigationSystem.h"

bool UDZItemSpawnUtilsLibrary::GetSafeLocationOnNavMesh(const UObject* WorldContextObject, const FVector& InLocation, FVector& OutResultLocation, const float& SearchRadius)
{
	if (!IsValid(WorldContextObject)) return false;
	if (!IsValid(WorldContextObject->GetWorld())) return false;
	
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(WorldContextObject->GetWorld());
	if (!NavSys) return false;
	
	// 1. 해당 지점이 NavMesh 위인지 확인.
	FNavLocation ProjectedLocation;
	bool bSuccess = NavSys->ProjectPointToNavigation(InLocation, ProjectedLocation, FVector(SearchRadius));
	if (!bSuccess) return false;
	
	// 2. 찾은 위치에서 아이템이 바닥에 묻히고 떨어지는 걸 방지하기 위해 약간 위로 올림
	OutResultLocation = ProjectedLocation.Location + FVector(0, 0, 50.f);
	return true;
}

bool UDZItemSpawnUtilsLibrary::GetSafeLocationOnNavMeshInRing(const UObject* WorldContextObject, const FVector& InLocation, FVector& OutResultLocation, const float& MinRadius, const float& MaxRadius, const int32& MaxRetries)
{
	if (!IsValid(WorldContextObject)) return false;
	if (!IsValid(WorldContextObject->GetWorld())) return false;
	
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(WorldContextObject->GetWorld());
	if (!NavSys) return false;
	
	for (int32 i = 0; i < MaxRetries; ++i)
	{
		// 1. 랜덤한 방향 벡터 생성 (XY 평면)
		FVector RandomDir = FMath::VRand(); // 모든 방향 랜덤 벡터
		RandomDir.Z = 0.f;                  // 위아래는 무시 (수평으로만)
		RandomDir.Normalize();

		// 2. 최소 ~ 최대 사이의 랜덤 거리 결정
		float RandomDist = FMath::RandRange(MinRadius, MaxRadius);
        
		// 3. 목표 지점 계산
		FVector TargetPoint = InLocation + (RandomDir * RandomDist);

		// 4. 해당 지점이 NavMesh 위인지 확인.
		FNavLocation ProjectedLocation;
		bool bSuccess = NavSys->ProjectPointToNavigation(TargetPoint, ProjectedLocation, FVector(MinRadius));
		if (!bSuccess) continue;
		
		// 5. 찾은 위치에서 아이템이 바닥에 묻히고 떨어지는 걸 방지하기 위해 약간 위로 올림
		OutResultLocation = ProjectedLocation.Location + FVector(0, 0, 50.f);
		return true;
	}
	
	return false;
}


