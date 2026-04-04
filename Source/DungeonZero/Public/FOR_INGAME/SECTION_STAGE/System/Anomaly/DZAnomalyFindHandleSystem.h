// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Subsystems/WorldSubsystem.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZFindAnomalyMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZAnomalyFindHandleSystem.generated.h"

/**
 * 어노말리 찾았다고 알림을 받으면 그걸 핸들하는 시스템
 */
UCLASS()
class DUNGEONZERO_API UDZAnomalyFindHandleSystem : public UWorldSubsystem
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
public:
	static UDZAnomalyFindHandleSystem* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Deinitialize() override;
	
#pragma endregion
//======================================================================================================================	
#pragma region FindAnomalyPI
	
	//━━━━━━━━━━━━━━━━━━━━
	// FindAnomalyPI
	//━━━━━━━━━━━━━━━━━━━━
protected:
	// 메시지 수신 함수
	void OnFindAnomalyMessageReceived(FGameplayTag Channel, const FDZFindAnomalyMSG& Payload);
	
#pragma endregion	
//======================================================================================================================	
#pragma region Data		
	
private:
	// 구독 핸들
	FGameplayMessageListenerHandle FindAnomalyListenerHandle;	
	
#pragma endregion
//======================================================================================================================		
};
