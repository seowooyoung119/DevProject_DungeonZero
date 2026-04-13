// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/StaticMeshActor/DZStaticMeshAnomalyActor.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZDoorMSG.h"
#include "FOR_INGAME/SECTION_ANOMALY/Interface/DZAnomalyMotionInterface.h"
#include "FOR_INGAME/SECTION_INTERACT/Interface/DZCommonInteractInterface.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZAnomalyDoor.generated.h"

class UDZAnomalyTriggerComponent;
class UWidgetComponent;
class UTimelineComponent;

UCLASS()
class DUNGEONZERO_API ADZAnomalyDoor : public ADZStaticMeshAnomalyActor, public IDZCommonInteractInterface, public IDZAnomalyMotionInterface
{
	GENERATED_BODY()

//======================================================================================================================
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	UFUNCTION()
	void OnRep_IsOpened();
	
	UFUNCTION()
	void OnRep_DoorSoundVarForRep();
	
#pragma endregion
//======================================================================================================================
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	ADZAnomalyDoor();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region DoorAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// DoorAPI
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	// 문 열림/닫힘 로직 (서버에서 실행)
	UFUNCTION(BlueprintCallable)
	void ToggleDoor(bool WantOpen);

protected:
	
	// 타임라인 업데이트 함수
	UFUNCTION() 
	void UpdateDoorRotation(float Value);

	
#pragma endregion
//======================================================================================================================
#pragma region component
protected:
		
	//━━━━━━━━━━━━━━━━━━━━
	// component
	//━━━━━━━━━━━━━━━━━━━━
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DZ")
	TObjectPtr<UStaticMeshComponent> DoorMesh = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
protected:

	//---------------------
	//  문 사운드
	//---------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DZ")
	TObjectPtr<USoundBase> DoorSound = nullptr;
	
	UPROPERTY(ReplicatedUsing = OnRep_DoorSoundVarForRep,EditAnywhere, BlueprintReadWrite, Category="DZ")
	int32 DoorSoundVarForRep = -1;
	
	//---------------------
	// 문 열고 닫기 관련
	//---------------------
	
	// 부드러운 움직임을 위한 타임라인
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="DZ") 
	TObjectPtr<UTimelineComponent> DoorTimeline = nullptr;

	// 부드러운 움직임을 위한 커브 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> DoorCurve = nullptr;

	// 문이 열리고 닫히는 회전각도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FRotator ClosedRotation = FRotator::ZeroRotator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FRotator OpenedRotation = FRotator::ZeroRotator;
	
	// 리플리케이션 변수: ReplicatedUsing을 통해 값이 변하면 OnRep 함수가 실행됨
	UPROPERTY(ReplicatedUsing = OnRep_IsOpened)
	bool bIsOpened = false;
	
	//---------------------
	//  스테이지 관련 데이터 처리
	//---------------------
	
	// 문이 스테이지 시작을 위한 문인지 체크
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	bool bIsDoorForStartTime = false;

	// 스테이지마다 리셋되어 딱 한번만 타이머 시작이 가능하도록 중복 방지하는 변수
	bool bIsDoorForStartTimeHasBeenUsed = true;
	
#pragma endregion
//======================================================================================================================
#pragma region 게임플레이_메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임플레이_메시지
	//━━━━━━━━━━━━━━━━━━━━
protected:
	
	// 메시지 수신 함수 (리셋용)
	void OnDoorResetReceived(FGameplayTag Channel, const FDZDoorMSG& Payload);

	// 구독 핸들
	FGameplayMessageListenerHandle TimeResetListenerHandle;
	
#pragma endregion
//======================================================================================================================
#pragma region 인터렉트_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_섹션
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// IDZCommonInteractInterface ~ 
	virtual void ToggleInteractWidget_Implementation(bool InWantOn) override;
	virtual void DoStandAloneInteractLogic_Implementation() override;
	// ~ IDZCommonInteractInterface
	
protected:
	
	// 위젯 컴포넌트 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UWidgetComponent> InteractWidgetComp = nullptr;

#pragma endregion
//======================================================================================================================	
#pragma region 어노말리_엔딩_펑션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리 엔딩 펑션
	//━━━━━━━━━━━━━━━━━━━━	
public:
	// GAS로 하기 비효율적이거나 액터와 연관이 되어 있을 경우 이 인터페이스의 API를 상속하여 로직을 추가한 뒤 GAS의 EndAbility 에서 인터페이스 호출 
	virtual void AnomalySealAdditionalFunction_Implementation() override { bIsAnomalySealed = true; };
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite, Category = "DZ")
	bool bIsAnomalySealed = false;
	
#pragma endregion
//======================================================================================================================	

};
