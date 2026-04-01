// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZStageLoadUnLoadManager.generated.h"

// 상위 모듈 명령에 따라 지정된 레벨을 로드 또는 언로드 실시

UCLASS()
class DUNGEONZERO_API ADZStageLoadUnLoadManager : public AActor
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	ADZStageLoadUnLoadManager();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
protected:
	// 준비 전 초기화 (들어온 레벨 언로드 실시)
	void OnPrepareMessageReceived(FGameplayTag GameplayTag, const FDZStageReadyMSG& Payload);
	
	// 준비 :  (1단계 -> 룸 로드)
	void OnReadyNewStageMessageReceived(FGameplayTag Channel, const FDZStageReadyMSG& Payload);
	UFUNCTION() void OnReadyNewStageLoadingFinished();
	
#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dz | Level")
	TMap<int32, TSoftObjectPtr<UWorld>> LevelToLoad;
	
	// 준비 핸들
	FGameplayMessageListenerHandle ReadyNewStageListenerHandle;
	
	// 디버그
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dz | Level")
	bool bWantPrintDebug = false;
	
#pragma endregion
//======================================================================================================================	
};
