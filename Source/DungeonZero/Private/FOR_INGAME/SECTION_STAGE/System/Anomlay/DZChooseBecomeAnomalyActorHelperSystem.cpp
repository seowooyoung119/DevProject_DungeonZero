// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZChooseBecomeAnomalyActorHelperSystem.h"

#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

UDZChooseBecomeAnomalyActorHelperSystem* UDZChooseBecomeAnomalyActorHelperSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZChooseBecomeAnomalyActorHelperSystem* ChooseBecomeAnomalyActorHelperSystem = World->GetSubsystem<UDZChooseBecomeAnomalyActorHelperSystem>();
	if (!IsValid(ChooseBecomeAnomalyActorHelperSystem)) return nullptr;
	
	return ChooseBecomeAnomalyActorHelperSystem;
}
	
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━

TArray<AActor*> UDZChooseBecomeAnomalyActorHelperSystem::ChooseRandomAnomalyActors_internal(const TArray<AActor*>& InPossibleActors, int32 MinCount, int32 MaxCount)
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return TArray<AActor*>();
	if (GetWorld()->GetNetMode() == NM_Client) return TArray<AActor*>();
		
	TArray<AActor*> SelectedActors;
    
	// 방어 코드: 후보가 없으면 빈 배열 반환
	if (InPossibleActors.Num() == 0) return SelectedActors;

	// 최소/최대 범위 내에서 몇 개를 뽑을지 결정 
	int32 TargetCount = FMath::RandRange(MinCount, MaxCount);

	// 데이터 테이블의 값이 후보 전체 개수보다 클 수 있으므로 클램핑(Clamping) 처리
	TargetCount = FMath::Clamp(TargetCount, 0, InPossibleActors.Num());

	// 3. 무작위 선택을 위해 원본 배열 복사 후 섞기
	TArray<AActor*> ShuffledActors = InPossibleActors;
    
	// 언리얼 기본 알고리즘을 사용해 배열을 무작위로 섞음
	const int32 LastIndex = ShuffledActors.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index)
		{
			ShuffledActors.Swap(i, Index);
		}
	}

	// 4. 앞에서부터 결정된 개수만큼 결과 배열에 추가
	for (int32 i = 0; i < TargetCount; ++i)
	{
		SelectedActors.Add(ShuffledActors[i]);
	}
	
	return SelectedActors;
}
#pragma endregion	
//======================================================================================================================	