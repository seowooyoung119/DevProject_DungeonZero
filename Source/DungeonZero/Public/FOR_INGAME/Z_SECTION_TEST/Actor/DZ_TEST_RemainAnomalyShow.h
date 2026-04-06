// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "DZ_TEST_RemainAnomalyShow.generated.h"

class UWidgetComponent;
class UStaticMeshComponent;

UCLASS()
class DUNGEONZERO_API ADZ_TEST_RemainAnomalyShow : public AActor
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	UFUNCTION()
	void OnRep_RemainAnomalyCount();
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━			
public:
	ADZ_TEST_RemainAnomalyShow();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 테스팅
	
	//━━━━━━━━━━━━━━━━━━━━
	// 테스팅
	//━━━━━━━━━━━━━━━━━━━━	
protected:
	
	void OnReMainAnomalyReceived(FGameplayTag Channel, const FDZStageRemainAnomalyMSG& Payload);

	// 핸들 
	FGameplayMessageListenerHandle RemainAnomalyListenerHandle;
	
	// 남은 갯수 
	UPROPERTY(ReplicatedUsing = OnRep_RemainAnomalyCount, EditAnywhere, BlueprintReadWrite, Category = "DZ | TEST")
	int32 RemainAnomalyCount = -1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UStaticMeshComponent> SignBoardRoot = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UWidgetComponent> SignBoardWidgetComponent = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
