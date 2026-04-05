// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAllowPlayerControlMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "GameFramework/PlayerController.h"
#include "DZPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZPlayerController : public APlayerController
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	UFUNCTION()
	void OnRep_IsVisibleAndMovable();
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	ADZPlayerController();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━

protected:
	
	// 메시지 수신 함수
	void OnCanMoveAndSeeReceived(FGameplayTag Channel, const FDZAllowPlayerControlMSG& Payload);	

	// 구독 핸들
	FGameplayMessageListenerHandle CanMoveAndSeeListenerHandle;
	
	// 움직이고 볼 수 있는가?
	UPROPERTY(ReplicatedUsing = OnRep_IsVisibleAndMovable, EditAnywhere, BlueprintReadWrite, Category = "DZ")
	bool IsVisibleAndMovable = true;
	
#pragma endregion
//======================================================================================================================		
	
	
};
