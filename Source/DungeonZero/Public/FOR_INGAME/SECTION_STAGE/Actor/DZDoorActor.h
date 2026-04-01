// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZDoorMSG.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZDoorActor.generated.h"

class UTimelineComponent;

UCLASS()
class DUNGEONZERO_API ADZDoorActor : public AActor
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
	
#pragma endregion
//======================================================================================================================
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	ADZDoorActor();
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
#pragma region 게임플레이_메시지	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임플레이_메시지
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	// 메시지 수신 시 실행될 함수 (문 열고 닫기)
	void OnDoorToggleMessageReceived(FGameplayTag Channel, const FDZDoorMSG& Payload);

	// 구독 핸들을 보관 (나중에 해제하기 위함)
	FGameplayMessageListenerHandle DoorToggleMessageHandle;

#pragma endregion
//======================================================================================================================	
#pragma region component
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> DoorMesh = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
protected:

	//---------------------
	// 문 열고 닫기 관련
	//---------------------
	
	// 부드러운 움직임을 위한 타임라인
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TObjectPtr<UTimelineComponent> DoorTimeline = nullptr;

	// 부드러운 움직임을 위한 커브 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> DoorCurve = nullptr;

	// 문이 열리고 닫히는 회전각도
	FRotator ClosedRotation = FRotator::ZeroRotator;
	FRotator OpenedRotation = FRotator::ZeroRotator;;
	
	// 리플리케이션 변수: ReplicatedUsing을 통해 값이 변하면 OnRep 함수가 실행됨
	UPROPERTY(ReplicatedUsing = OnRep_IsOpened)
	bool bIsOpened = false;
	
	//---------------------
	// 레벨 관련
	//---------------------
	
	// 이 문이 소속된 레벨 (에디터에서 설정하거나 자동으로 할당)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DoorLevel = -1;
	
	//---------------------
	// 디버그
	//---------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWantPrintDebug = false;
	
#pragma endregion
//======================================================================================================================		
};
