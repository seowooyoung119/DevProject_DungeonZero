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
#pragma region onRep
public:
	
	UFUNCTION()
	void OnRep_IsOpened();
	
#pragma endregion
//======================================================================================================================
#pragma region LifeCycle
public:
	ADZDoorActor();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
#pragma endregion
//======================================================================================================================	
#pragma region DoorAPI	

public:
	// 문 열림/닫힘 로직 (서버에서 실행)
	UFUNCTION(BlueprintCallable)
	void ToggleDoor(bool WantOpen);

protected:
	
	// 타임라인 업데이트 함수
	UFUNCTION() void UpdateDoorRotation(float Value);

	// 메시지 수신 시 실행될 함수 (문 열고 닫기)
	void OnDoorToggleMessageReceived(FGameplayTag Channel, const FDZDoorMSG& Payload);

#pragma endregion
//======================================================================================================================	
#pragma region component
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> DoorMesh = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region Data
protected:
	
	// 리플리케이션 변수: ReplicatedUsing을 통해 값이 변하면 OnRep 함수가 실행됨
	UPROPERTY(ReplicatedUsing = OnRep_IsOpened)
	bool bIsOpened;
	
	// 부드러운 움직임을 위한 타임라인
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	TObjectPtr<UTimelineComponent> DoorTimeline = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> DoorCurve = nullptr;

protected:
	FRotator ClosedRotation;
	FRotator OpenedRotation;
	
	// 구독 핸들을 보관 (나중에 해제하기 위함)
	FGameplayMessageListenerHandle DoorToggleMessageHandle;

	// 이 문이 소속된 레벨 (에디터에서 설정하거나 자동으로 할당)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DoorLevel = -1;
	
#pragma endregion
//======================================================================================================================		
};
