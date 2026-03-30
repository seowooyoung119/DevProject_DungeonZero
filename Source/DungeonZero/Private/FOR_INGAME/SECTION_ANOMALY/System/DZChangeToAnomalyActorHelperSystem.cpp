// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/System/DZChangeToAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "FOR_INGAME/SECTION_STAGE/Library/StageBalanceDataLibrary.h"

//======================================================================================================================	
#pragma region Getter	
UDZChangeToAnomalyActorHelperSystem* UDZChangeToAnomalyActorHelperSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZChangeToAnomalyActorHelperSystem* ChangeToAnomalyActorHelperSystem = World->GetSubsystem<UDZChangeToAnomalyActorHelperSystem>();
	if (!IsValid(ChangeToAnomalyActorHelperSystem)) return nullptr;
	
	return ChangeToAnomalyActorHelperSystem;
}
#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle
void UDZChangeToAnomalyActorHelperSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UStageBalanceDataLibrary::CacheAnomalyDataToMap(AnomalyDataMap);
	UStageBalanceDataLibrary::DebugLogAnomalyMap(AnomalyDataMap);
}

#pragma endregion
//======================================================================================================================	
#pragma region StageAPI
TArray<AActor*> UDZChangeToAnomalyActorHelperSystem::ReplaceWithAnomalyActors_internal(const TArray<AActor*>& SelectedActors)
{
	// 임시 데이터 생성 및 체크
	TArray<AActor*> SpawnedAnomalies;
	UWorld* World = GetWorld();
	if (!World || SelectedActors.Num() == 0) return SpawnedAnomalies;

	// 1. 루프 시작: 랜덤으로 선택된 후보 액터들을 순회
	for (AActor* OriginalActor : SelectedActors)
	{
		// 유효 체크
		if (!IsValid(OriginalActor)) continue;

		// 2. 액터의 태그를 순회하며 캐싱된 맵(AnomalyDataMap)에 키값이 있는지 확인
		FDZAnomalySettingTable* TargetSetting = nullptr;
		for (const FName& ActorTag : OriginalActor->Tags)
		{
			if (AnomalyDataMap.Contains(ActorTag))
			{
				TargetSetting = &AnomalyDataMap[ActorTag];
				break; // 매칭되는 첫 번째 태그 발견 시 중단
			}
		}

		// 3. 매칭되는 설정 데이터가 있고, 스폰할 클래스가 지정되어 있다면 교체 진행
		if (TargetSetting && TargetSetting->AnomalyClass_Anomaly)
		{
			// 원본 트래스폼 임시 저장
			FTransform SpawnTransform = OriginalActor->GetActorTransform();
            
			// 스폰 파라미터 설정
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Owner = OriginalActor->GetOwner();

			// 어노말리 액터 스폰
			AActor* NewAnomaly = World->SpawnActor<AActor>(TargetSetting->AnomalyClass_Anomaly, SpawnTransform, SpawnParams);
			if (!IsValid(NewAnomaly)) continue;
			
			// 어노말리 스폰 배열게 추가 
			SpawnedAnomalies.Add(NewAnomaly);
			
			// 4. 기존 원본 액터 파괴
			OriginalActor->Destroy();
			UE_LOG(LogTemp, Log, TEXT("Anomaly Replaced: %s spawned at %s"), *NewAnomaly->GetName(), *SpawnTransform.GetLocation().ToString());
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("ReadyNewStage 3단계 : 룸 로드 매니저 : 변환 완료"));
	return SpawnedAnomalies;
}

#pragma endregion
//======================================================================================================================	