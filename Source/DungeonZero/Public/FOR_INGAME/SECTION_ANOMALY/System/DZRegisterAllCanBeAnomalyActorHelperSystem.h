// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZRegisterAllCanBeAnomalyActorHelperSystem.generated.h"

/**
 * 역할 : 스테이지에 어노말리 가능한 모든 액터를 수집하는 시스템 
 */
UCLASS()
class DUNGEONZERO_API UDZRegisterAllCanBeAnomalyActorHelperSystem : public UWorldSubsystem
{
	friend class UDZStageControlSystem;
	
	GENERATED_BODY()
//======================================================================================================================	
#pragma region Getter
public:
	static UDZRegisterAllCanBeAnomalyActorHelperSystem* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================
#pragma region LifeCycle
	
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;
#pragma endregion
//======================================================================================================================
#pragma region RegisterAPI

public:
	FORCEINLINE void RegisterAllCanBeAnomalyActor(AActor* Actor) { PossibleActors.AddUnique(Actor);};
	
#pragma endregion
//======================================================================================================================
#pragma region StageAPI
	
protected:
	// 준비 전 초기화 (들어온 레벨 언로드 실시)
	void OnPrepareMessageReceived(FGameplayTag GameplayTag, const FDZStageMSG& Payload);
	
#pragma endregion
//======================================================================================================================
#pragma region Data
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> PossibleActors;
	
	// 초기화 핸들
	FGameplayMessageListenerHandle PrepareListenerHandle;
	
#pragma endregion	
//======================================================================================================================
	
};
