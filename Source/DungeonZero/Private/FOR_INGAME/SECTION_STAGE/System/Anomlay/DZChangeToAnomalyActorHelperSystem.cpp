// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZChangeToAnomalyActorHelperSystem.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "FOR_INGAME/SECTION_STAGE/Library/StageAllInOneHelpLibrary.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

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
#pragma region StageAPI
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━

TArray<AActor*> UDZChangeToAnomalyActorHelperSystem::ReplaceWithAnomalyActors_internal(const TArray<AActor*>& SelectedActors)
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return TArray<AActor*>();
	if (GetWorld()->GetNetMode() == NM_Client) return TArray<AActor*>();
		
	// 임시 데이터 생성 및 체크
	TArray<AActor*> SpawnedAnomalies;
	
	// 1. 루프 시작: 랜덤으로 선택된 후보 액터들을 순회
	for (AActor* OriginalActor : SelectedActors)
	{
		// 유효 체크
		if (!IsValid(OriginalActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("!IsValid(OriginalActor) 실패"))
			continue;
		}
		
		// 1. 기존 원본 액터 숨김 [3]
		if (!OriginalActor->GetClass()->ImplementsInterface(UDZCommonPlayRoleInterface::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("기존 원본 액터 숨김 실패"))
			continue;
		}
		IDZCommonPlayRoleInterface::Execute_ToggleHiddenInGame(OriginalActor, false, false);
		
		// 2. 액터의 태그를 순회하며 캐싱된 맵(AnomalyDataMap)에 키값이 있는지 확인
		FDZAnomalySettingTable* TargetSetting = UStageAllInOneHelpLibrary::IsAnyAnomalyTagIsMatch(this, OriginalActor);
		if (!TargetSetting)
		{
			UE_LOG(LogTemp, Warning, TEXT(" 액터의 태그를 순회하며 캐싱된 맵(AnomalyDataMap)에 키값이 있는지 확인 실패"))
			UE_LOG(LogTemp, Warning, TEXT("%s"), *OriginalActor->GetName())
			continue;
		}
		
		// 3. 스폰할 클래스가 지정되어 있는지 확인
		if (!TargetSetting->AnomalyClass_Anomaly)
		{
			UE_LOG(LogTemp, Warning, TEXT("스폰할 클래스가 지정되어 있는지 확인 실패 "))
			continue;
		}
		
		// 원본 트래스폼 임시 저장
		FTransform SpawnTransform = OriginalActor->GetActorTransform();
            
		// 스폰 파라미터 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = OriginalActor->GetOwner();

		// 4. 어노말리 액터 스폰
		AActor* NewAnomaly = GetWorld()->SpawnActor<AActor>(TargetSetting->AnomalyClass_Anomaly, SpawnTransform, SpawnParams);
		if (!IsValid(NewAnomaly))
		{
			UE_LOG(LogTemp, Warning, TEXT("어노말리 액터 스폰 실패"))
			continue;
		}
		
		// 어노말리 스폰 배열게 추가 
		SpawnedAnomalies.Add(NewAnomaly);
	}

	return SpawnedAnomalies;
}

#pragma endregion
//======================================================================================================================	