// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/DZAnomalyFindHandleSystem.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/DZStageControlSystem.h"

//======================================================================================================================	
#pragma region Getter
UDZAnomalyFindHandleSystem* UDZAnomalyFindHandleSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZAnomalyFindHandleSystem* AnomalyFindHandleSystem = World->GetSubsystem<UDZAnomalyFindHandleSystem>();
	if (!IsValid(AnomalyFindHandleSystem)) return nullptr;
	
	return AnomalyFindHandleSystem;
}
	
#pragma endregion
//======================================================================================================================
#pragma region LifeCycle
void UDZAnomalyFindHandleSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FindAnomalyListenerHandle = MessageSubsystem.RegisterListener<FDZFindAnomalyMSG>(DZ::FindAnomaly::DZ_SEND_FIND_ANOMLAY, this, &UDZAnomalyFindHandleSystem::OnFindAnomalyMessageReceived);
}

void UDZAnomalyFindHandleSystem::Deinitialize()
{
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(FindAnomalyListenerHandle);
	}
	Super::Deinitialize();
}
#pragma endregion
//======================================================================================================================	
#pragma region FindAnomalyPI
void UDZAnomalyFindHandleSystem::OnFindAnomalyMessageReceived(FGameplayTag Channel, const FDZFindAnomalyMSG& Payload)
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return;
	if (GetWorld()->GetNetMode() == NM_Client) return;

	// 데이터 체크
	UDZStageControlSystem* StageControlSystem = UDZStageControlSystem::Get(this);
	if (!IsValid(StageControlSystem)) return;
	if (!IsValid(Payload.FindAnomalyActor)) return;

	// 어노말리 있는지 확인 
	bool FindResult = false;
	for (auto& AnomalyActor : StageControlSystem->AnomalyActors)
	{
		if (AnomalyActor == Payload.FindAnomalyActor)
		{
			FindResult = true;
			break;
		}
	}

	// 있으면 빼버리고 카운트 차감 -> 성공 핸들 처리 
	if (FindResult == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("RunningStage 단계 : 어노말리 찾기 핸들 시스템 : 어노말리인데 현재 UDZAnomalyFindHandleSystem 에서 부숨"));
		UE_LOG(LogTemp, Warning, TEXT("RunningStage 단계 : 어노말리 찾기 핸들 시스템 : 나중에 이 테스트 코드는 반드시 제거할 것."));
		if (IsValid(Payload.FindAnomalyActor)) Payload.FindAnomalyActor->Destroy();
		UE_LOG(LogTemp, Warning, TEXT("RunningStage 단계 : 어노말리 찾기 핸들 시스템 : 나중에 이 테스트 코드는 반드시 제거할 것."));
		
		StageControlSystem->AnomalyCount--;
		StageControlSystem->AnomalyActors.Remove(Payload.FindAnomalyActor);
		
		// 만약에 카운트가 0이거나 다 찾아서 배열에 남은 게 없으면? -> 다 찾았음 호출 
		if (StageControlSystem->AnomalyCount == 0 || StageControlSystem->AnomalyActors.Num() == 0)
		{
			StageControlSystem->DoRunningStage_Internal_HandleIfAllAnomalyFound();
		}
		UE_LOG(LogTemp, Warning, TEXT("RunningStage 단계 : 어노말리 찾기 핸들 시스템 : 어노말리임"));
	}
	
	// 없으면 -> 실패 핸들 처리 
	else
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZFindResultAnomalyMSG FindResultPayload;
		FindResultPayload.bIsFindAnomaly = false;
		MessageSubsystem.BroadcastMessage(DZ::FindAnomaly::DZ_RESOULT_OF_FIND_ANOMLAY, FindResultPayload);
		UE_LOG(LogTemp, Warning, TEXT("RunningStage 단계 : 어노말리 찾기 핸들 시스템 : 어노말리 아님"));
	}
}

#pragma endregion
//======================================================================================================================	