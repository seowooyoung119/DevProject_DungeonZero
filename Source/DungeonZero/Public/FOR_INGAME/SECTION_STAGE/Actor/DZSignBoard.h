// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZSignBoard.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZSignBoard : public AActor
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	UFUNCTION()
	void OnRep_CurrentLevel();
	
#pragma endregion
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZSignBoard();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region SignBoardAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// SignBoardAPI
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	// 메시지 수신 함수
	void OnCurrentLevelNoticeReceived(FGameplayTag Channel, const FDZStageMSG& Payload);
	
	// 구독 핸들
	FGameplayMessageListenerHandle CurrentLevelNoticeListenerHandle;
	
#pragma endregion
//======================================================================================================================		
#pragma region 컴포넌트_및_데이터	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트 및 데이터
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	void UpdateUIbyCurrentLevel();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UStaticMeshComponent> SignBoardRoot = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UWidgetComponent> SignBoardWidgetComponent = nullptr;
	
	UPROPERTY(ReplicatedUsing = OnRep_CurrentLevel, EditAnywhere, BlueprintReadOnly, Category = "DZ")
	int32 CurrentLevel = 0;

#pragma endregion
//======================================================================================================================		
};
