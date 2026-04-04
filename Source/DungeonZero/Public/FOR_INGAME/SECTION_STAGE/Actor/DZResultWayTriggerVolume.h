// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAllowPlayerControlMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZResultWayTriggerVolume.generated.h"

class UBoxComponent;

UCLASS()
class DUNGEONZERO_API ADZResultWayTriggerVolume : public AActor
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
public:
	ADZResultWayTriggerVolume();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion
//======================================================================================================================	
#pragma region 이상현상이동트리거볼륨
	
	//━━━━━━━━━━━━━━━━━━━━
	// 이상현상이동트리거볼륨
	//━━━━━━━━━━━━━━━━━━━━	

protected:
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "DZ")
	TObjectPtr<UBoxComponent> TriggerBoxComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DZ")
	bool IsMoveLogicHasStart = false;	

#pragma endregion
//======================================================================================================================	
#pragma region 게임플레이메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임플레이메시지
	//━━━━━━━━━━━━━━━━━━━━
	
protected:

	// 메시지 수신 함수 (리셋용)
	void OnAllowPlayerSeeAndMoveReceived(FGameplayTag Channel, const FDZAllowPlayerControlMSG& Payload);

	// 구독 핸들
	FGameplayMessageListenerHandle AllowPlayerControlListenerHandle;

#pragma endregion
//======================================================================================================================		
};
