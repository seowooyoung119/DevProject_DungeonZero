// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZGameModeMSG.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZInGameGM.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZInGameGM : public AGameModeBase
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 죽음_처리
	
	//━━━━━━━━━━━━━━━━━━━━
	// 죽음 처리
	//━━━━━━━━━━━━━━━━━━━━
protected:
	
	// 플레이어가 죽을 때마다 수신 
	void OnPlayerDeathReceived(FGameplayTag Channel, const FDZGameModeDeathCountMSG& Payload);
	
	UFUNCTION(BlueprintImplementableEvent)
	void GoToLobbyIfAllDead();
	
	// 구독 핸들
	FGameplayMessageListenerHandle PlayerDeathListenerHandle;

#pragma endregion
//======================================================================================================================	

};
