// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZChooseBecomeAnomalyActorHelperSystem.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

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

TArray<AActor*> UDZChooseBecomeAnomalyActorHelperSystem::ChooseRealAnomalyActors_internal(const TArray<AActor*>& InPossibleActors, int32 MinCount, int32 MaxCount)
{
	// 1. 클라이언트 패스
	if (!IsValid(GetWorld())) return TArray<AActor*>();
	if (GetWorld()->GetNetMode() == NM_Client) return TArray<AActor*>();
		
	// 2. 변환될 원본들을 담을 배열
	TArray<AActor*> SelectedActors;
    
	// 3. 원본이 하나도 없으면 없으면 빈 배열 반환
	if (InPossibleActors.Num() == 0) return SelectedActors;

	// 4. 최소/최대 범위 내에서 몇 개를 뽑을지 결정 
	int32 TargetCount = FMath::RandRange(MinCount, MaxCount);

	// 5. 데이터 테이블의 값이 후보 전체 개수보다 클 수 있으므로 클램핑(Clamping) 처리
	TargetCount = FMath::Clamp(TargetCount, 0, InPossibleActors.Num());

	// 6. 선택을 위해 원본 배열 복사 
	TArray<AActor*> ShuffledActors = InPossibleActors;

	// 7. 원본들 중에서 이전에 선택된 원본 제거 
	for (auto& PreviousSelectedActor : PreviousSelectedActors)
	{
		ShuffledActors.Remove(PreviousSelectedActor);
	}

	// 8. 만약에 선택 가능한 원본이 없거나 부족한 경우 리셋
	if (ShuffledActors.Num() < TargetCount || ShuffledActors.IsEmpty())
	{
		PreviousSelectedActors.Empty();
		ShuffledActors = InPossibleActors;
	}
	
	// 9. 언리얼 기본 알고리즘을 사용해 배열을 무작위로 섞음
	const int32 LastIndex = ShuffledActors.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index)
		{
			ShuffledActors.Swap(i, Index);
		}
	}

	// 10. 앞에서부터 결정된 개수만큼 결과 배열에 추가 (선택 및, 이전 선택에 추가)
	for (int32 i = 0; i < TargetCount; ++i)
	{
		SelectedActors.Add(ShuffledActors[i]);
		PreviousSelectedActors.Add(ShuffledActors[i]);
	}
	
	return SelectedActors;
}


TArray<FDZFakeAnomalySeeInfo> UDZChooseBecomeAnomalyActorHelperSystem::ChooseFakeAnomalyActors_internal(const TArray<AActor*>& InPossibleActors, TArray<AActor*>& RealAnomaliesSelectedActors, int32 MinCount, int32 MaxCount)
{
	// 0. 결과를 담을 배열 
	TArray<FDZFakeAnomalySeeInfo> ResultInfos;
	
	// 1. 클라이언트 패스
	if (!IsValid(GetWorld()))
	{
		return TArray<FDZFakeAnomalySeeInfo>();
	}
	if (GetWorld()->GetNetMode() == NM_Client)
	{
		return TArray<FDZFakeAnomalySeeInfo>();
	}

	// 2. 원본 배열 복사
	TArray<AActor*> FakeCandidates = InPossibleActors;

	// 3. 진짜를 제외한 가짜 후보군 추출
	for (AActor* Real : RealAnomaliesSelectedActors)
	{
		FakeCandidates.Remove(Real);
	}
	
	// 4. 후보가 없을 경우 
	if (FakeCandidates.Num() == 0) return ResultInfos;
	
	// 5. 유효한 플레이어 목록 가져오기
	TArray<APlayerState*> AllPlayers;
	for (APlayerState* PS : GetWorld()->GetGameState()->PlayerArray)
	{
		if (IsValid(PS)) AllPlayers.Add(PS);
	}

	// 플레이어 숫자
	const int32 PlayerCount = AllPlayers.Num();

	// 플레이어가 없을 경우 
	if (PlayerCount == 0) return ResultInfos;
	
	// 6. 임시 맵 생성: 어떤 원본 액터(Key)를 어떤 플레이어들(Value)이 보게 될 것인가?
	// 이 맵을 통해 "누가 무엇을 보는지" 역으로 추적.
	TMap<AActor*, TArray<APlayerState*>> AssignmentMap;
	
	for (APlayerState* PS : AllPlayers)
	{
		// 각 플레이어마다 랜덤하게 몇 개의 가짜를 볼지 결정
		int32 ItemsForThisPlayer = FMath::RandRange(MinCount, MaxCount);
        
		// 후보군 셔플
		TArray<AActor*> ShuffledForPlayer = FakeCandidates;
		for (int32 i = ShuffledForPlayer.Num() - 1; i > 0; --i)
		{
			ShuffledForPlayer.Swap(i, FMath::RandRange(0, i));
		}
		
		// 결정된 개수만큼 플레이어에게 할당
		for (int32 j = 0; j < FMath::Min(ItemsForThisPlayer, ShuffledForPlayer.Num()); ++j)
		{
			AActor* TargetActor = ShuffledForPlayer[j];
			AssignmentMap.FindOrAdd(TargetActor).Add(PS);
		}
	}
	
	// 4. 전체 일치 방지 검증
	// 특정 액터를 모든 플레이어가 보게 되었다면, 그 액터의 명단에서 랜덤하게 한 명을 제거.
	for (auto& Elem : AssignmentMap)
	{
		TArray<APlayerState*>& Viewers = Elem.Value;
        
		// 만약 이 가짜를 모든 플레이어가 본다면? (진짜와 구분 불가능 상황)
		if (PlayerCount > 1 && Viewers.Num() == PlayerCount)
		{
			// 랜덤하게 한 명을 명단에서 빼버림 -> 이제 이 이상현상은 '가짜'가 됨
			int32 RemoveIndex = FMath::RandRange(0, Viewers.Num() - 1);
			Viewers.RemoveAt(RemoveIndex);
		}

		// 최소 한 명은 보게 설정된 경우에만 결과에 추가
		if (Viewers.Num() > 0)
		{
			FDZFakeAnomalySeeInfo Info;
			Info.OriginActor = Elem.Key;
            
			// 구조체에 추가
			for (APlayerState* PS : Viewers)
			{
				Info.CanSeePlayers.Add(PS);
			}
			ResultInfos.Add(Info);
		}
	}

	return ResultInfos;
	
}


#pragma endregion	
//======================================================================================================================	