// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/System/DZRegisterAllCanBeAnomalyActorHelperSystem.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "GameFramework/GameplayMessageSubsystem.h"

//======================================================================================================================	
#pragma region Getter

UDZRegisterAllCanBeAnomalyActorHelperSystem* UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem = World->GetSubsystem<UDZRegisterAllCanBeAnomalyActorHelperSystem>();
	if (!IsValid(RegisterAllCanBeAnomalyActorHelperSystem)) return nullptr;
	
	return RegisterAllCanBeAnomalyActorHelperSystem;
	
}

#pragma endregion
//======================================================================================================================
#pragma region LifeCycle

void UDZRegisterAllCanBeAnomalyActorHelperSystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	// 구독 : 초기화
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	PrepareListenerHandle = MessageSubsystem.RegisterListener<FDZStageMSG>(DZ::Stage::DZ_STAGE_READYNEWSTAGE, this, &UDZRegisterAllCanBeAnomalyActorHelperSystem::OnPrepareMessageReceived);
}

void UDZRegisterAllCanBeAnomalyActorHelperSystem::Deinitialize()
{
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(PrepareListenerHandle);
	}
	Super::Deinitialize();
}

#pragma endregion
//======================================================================================================================
#pragma region StageAPI

void UDZRegisterAllCanBeAnomalyActorHelperSystem::OnPrepareMessageReceived(FGameplayTag GameplayTag, const FDZStageMSG& Payload)
{
	PossibleActors.Empty();
	UE_LOG(LogTemp, Warning, TEXT("Prepare : 원본 액터 등록 시스템 배열 초기화"));
}

#pragma endregion	
//======================================================================================================================