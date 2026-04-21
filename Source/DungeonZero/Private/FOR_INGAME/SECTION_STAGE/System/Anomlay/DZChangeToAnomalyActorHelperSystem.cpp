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

TArray<AActor*> UDZChangeToAnomalyActorHelperSystem::ReplaceWithRealAnomalyActors_internal(const TArray<AActor*>& SelectedActors)
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return TArray<AActor*>();
	if (GetWorld()->GetNetMode() == NM_Client) return TArray<AActor*>();
		
	// 임시 데이터 생성 및 체크
	TArray<AActor*> SpawnedRealAnomalies;
	
	// 1. 루프 시작: 랜덤으로 선택된 후보 액터들을 순회
	for (AActor* OriginalActor : SelectedActors)
	{
		// 유효 체크
		if (!IsValid(OriginalActor)) continue;
		
		// 1. 기존 원본 액터 숨김
		if (!OriginalActor->GetClass()->ImplementsInterface(UDZCommonPlayRoleInterface::StaticClass())) continue;
		IDZCommonPlayRoleInterface::Execute_ToggleHiddenInGame(OriginalActor, false, false);
		
		// 2. 액터의 태그를 순회하며 캐싱된 맵(AnomalyDataMap)에 키값이 있는지 확인
		FDZAnomalySettingTable* TargetSetting = UStageAllInOneHelpLibrary::IsAnyAnomalyTagIsMatch(this, OriginalActor);
		if (!TargetSetting) continue;
		
		// 3. 스폰할 클래스가 지정되어 있는지 확인
		if (!TargetSetting->AnomalyClass_Anomaly) continue;
		
		// 진짜 원본 트래스폼 임시 저장
		FTransform SpawnTransform = OriginalActor->GetActorTransform();
            
		// 스폰 파라미터 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = OriginalActor->GetOwner();

		// 4. 진짜 어노말리 액터 스폰
		AActor* NewAnomaly = GetWorld()->SpawnActor<AActor>(TargetSetting->AnomalyClass_Anomaly, SpawnTransform, SpawnParams);
		if (!IsValid(NewAnomaly)) continue;
		
		// 5. 진짜 어노말리 스폰 배열게 추가 
		SpawnedRealAnomalies.Add(NewAnomaly);
	}

	return SpawnedRealAnomalies;
}

TArray<AActor*> UDZChangeToAnomalyActorHelperSystem::ReplaceWithFakeAnomalyActors_internal(const TArray<FDZFakeAnomalySeeInfo>& FakeSelectedActors)
{
	// 임시 데이터 생성 및 체크
	TArray<AActor*> SpawnedFakeAnomalies;
	
	// 1. 루프 시작: 랜덤으로 선택된 후보 액터들을 순회
	for (auto& FakeSelectedActor : FakeSelectedActors)
	{
		// 유효 체크
		if (!IsValid(FakeSelectedActor.OriginActor)) continue;
		
		// 2. 액터의 태그를 순회하며 캐싱된 맵(AnomalyDataMap)에 키값이 있는지 확인
		FDZAnomalySettingTable* TargetSetting = UStageAllInOneHelpLibrary::IsAnyAnomalyTagIsMatch(this, FakeSelectedActor.OriginActor);
		if (!TargetSetting) continue;
		
		// 3. 스폰할 클래스가 지정되어 있는지 확인
		if (!TargetSetting->AnomalyClass_Anomaly) continue;
		
		// 4. 가짜 원본 트래스폼 임시 저장
		FTransform SpawnTransform = FakeSelectedActor.OriginActor->GetActorTransform();
            
		// 5. 스폰 파라미터 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = FakeSelectedActor.OriginActor->GetOwner();

		// 4. 가짜 어노말리 액터 스폰
		AActor* NewAnomaly = GetWorld()->SpawnActor<AActor>(TargetSetting->AnomalyClass_Anomaly, SpawnTransform, SpawnParams);
		if (!IsValid(NewAnomaly)) continue;
		
		// TODO : 가짜 어노말리라고 설정하게 해야함.
		// TODO : 가짜 어노말리에게 FDZFakeAnomalySeeInfo 정보를 넘겨줘야함. 
		// 이 정보에는 자신이 원래 원본이 무엇이었는지, 볼 수 있는 플레이어가 누군인지 적혀 있음.
		// 이 정보에 따라서 가짜 어노말리는 다음과 같은 작업을 해야함. 
		// 1. 먼저 서버에서 호스트가 자신을 볼 수 있는지 판단 -> 원본 또는 자신을 숨기거나 콜리전을 꺼야 함.
		// 2. 클라이언트로 정보를 보내 자신을 볼 수 있는지 판단 -> 원본 또는 자신을 숨기거나 콜리전을 꺼야 함.
		// 이렇게 해야 각각 로컬에서 이상현상이 보일 수 있음. 서로가 각자 다른 가짜를 볼 수 있음.
		// 때문에 콜리전과 숨김 처리를 onRep 으로 호출해서는 안 됨. 호스트가 안 보인다고 꺼버렸는데 클라가 봐야 하는데 꺼져서 보일 수 있음.
		
		// 가짜 어노말리 스폰 배열게 추가 
		SpawnedFakeAnomalies.Add(NewAnomaly);
	}

	return SpawnedFakeAnomalies;
	
}

#pragma endregion
//======================================================================================================================	