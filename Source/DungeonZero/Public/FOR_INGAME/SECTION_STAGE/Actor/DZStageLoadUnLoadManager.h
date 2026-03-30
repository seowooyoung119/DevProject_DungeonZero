// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZStageLoadUnLoadManager.generated.h"

UCLASS()
class DUNGEONZERO_API ADZStageLoadUnLoadManager : public AActor
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region LifeCycle
public:
	ADZStageLoadUnLoadManager();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	
protected:
	// 준비 전 초기화 (들어온 레벨 언로드 실시)
	void OnPrepareMessageReceived(FGameplayTag GameplayTag, const FDZStageReadyMSG& Payload);
	
	// 준비 :  (1단계 -> 룸 로드)
	void OnReadyNewStageMessageReceived(FGameplayTag Channel, const FDZStageReadyMSG& Payload);
	UFUNCTION() void OnReadyNewStageLoadingFinished();
#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dz | Level")
	TMap<int32, TSoftObjectPtr<UWorld>> LevelToLoad;
	
	// 준비 핸들
	FGameplayMessageListenerHandle ReadyNewStageListenerHandle;
	
#pragma endregion
//======================================================================================================================	
};
