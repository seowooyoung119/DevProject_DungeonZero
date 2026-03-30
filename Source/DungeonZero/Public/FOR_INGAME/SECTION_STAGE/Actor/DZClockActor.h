// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZClockActor.generated.h"

UCLASS()
class DUNGEONZERO_API ADZClockActor : public AActor
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region OnRep
public:
	UFUNCTION()
	void OnRep_TimeLeft();
#pragma endregion
//======================================================================================================================	
#pragma region LifeCycle
public:
	ADZClockActor();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
#pragma endregion
//======================================================================================================================	
#pragma region TimeAPI	
	// 메시지 수신 함수
	void OnTimeReduceReceived(FGameplayTag Channel, const FDZTimeMSG& Payload);
	void OnTimeOverReceived(FGameplayTag Channel, const FDZTimeMSG& Payload);

#pragma endregion
//======================================================================================================================	
#pragma region Data		
private:
	// 구독 핸들
	FGameplayMessageListenerHandle TimeReduceListenerHandle;
	FGameplayMessageListenerHandle TimeOverListenerHandle;
	
	// 시간 
	UPROPERTY(ReplicatedUsing = OnRep_TimeLeft)
	float TimeLeft;
	
#pragma endregion
//======================================================================================================================	
};
