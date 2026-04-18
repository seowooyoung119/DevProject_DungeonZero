// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAIGCMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZAIControllerBase.generated.h"

UCLASS()
class DUNGEONZERO_API ADZAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	ADZAIControllerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:

	void OnGCCallReceived(FGameplayTag Channel, const FDZAIGCMSG& Payload);
	
	// 핸들 
	FGameplayMessageListenerHandle OnGCCallListenerHandle;
};
