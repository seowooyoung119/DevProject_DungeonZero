// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZAnomalyFindHandleSystem.h"

#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"

#include "AbilitySystemComponent.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

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
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

void UDZAnomalyFindHandleSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	// 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FindAnomalyListenerHandle = MessageSubsystem.RegisterListener<FDZFindAnomalyMSG>(DZ::FindAnomalyMSG::DZ_SEND_FIND_ANOMLAY, this, &UDZAnomalyFindHandleSystem::OnFindAnomalyMessageReceived);
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

	//━━━━━━━━━━━━━━━━━━━━
	// FindAnomalyPI
	//━━━━━━━━━━━━━━━━━━━━

void UDZAnomalyFindHandleSystem::OnFindAnomalyMessageReceived(FGameplayTag Channel, const FDZFindAnomalyMSG& Payload)
{
	// 클라이언트 패스
	if (!IsValid(GetWorld())) return;
	if (GetWorld()->GetNetMode() == NM_Client) return;

	// 데이터 모듈 체크 
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;

	// 어노말리 있는지 확인 
	bool FindResult = StageRuntimePlayDataModule->HandleIsThereAnyAnomaly(Payload.FindAnomalyActor);

	// 성공 핸들 처리 
	if (FindResult == true)
	{
		StageRuntimePlayDataModule->HandleOnFoundAnomaly(Payload.FindAnomalyActor);
		
		//-------------------------------------
		// 복원 임시 테스트 
		if (IsValid(Payload.FindAnomalyActor))
		{
			ADZAnomalyActorBase* AnomalyActor = Cast<ADZAnomalyActorBase>(Payload.FindAnomalyActor);
			if (UAbilitySystemComponent* ASC = AnomalyActor->GetAbilitySystemComponent())
			{
				ASC->CancelAbilities(); // 어빌리티 종료
				ASC->ClearAllAbilities(); // 어빌리티 삭제
				// Destroy 없음 → 액터 그대로 남음
			}
		}
		// 복원 임시 테스트 
		//-------------------------------------
		
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZFindResultAnomalyMSG FindResultPayload;
		FindResultPayload.bIsFindAnomaly = true;
		MessageSubsystem.BroadcastMessage(DZ::FindAnomalyMSG::DZ_RESOULT_OF_FIND_ANOMLAY, FindResultPayload);
	}
	
	// 실패 핸들 처리 
	else
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZFindResultAnomalyMSG FindResultPayload;
		FindResultPayload.bIsFindAnomaly = false;
		MessageSubsystem.BroadcastMessage(DZ::FindAnomalyMSG::DZ_RESOULT_OF_FIND_ANOMLAY, FindResultPayload);
	}
	
	// 남은 어노 말리 발송 (성공, 실패 여부 상관 없이)
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		FDZStageRemainAnomalyMSG StageRemainAnomalyMSG;
		StageRemainAnomalyMSG.StageRemainAnomaly = StageRuntimePlayDataModule->GetAnomalyCount();
		MessageSubsystem.BroadcastMessage(DZ::StageMSG::DZ_STAGE_REMAINANOMLAY_NOTICE, StageRemainAnomalyMSG);
		
	}	
}

#pragma endregion
//======================================================================================================================	