// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZClockActor.generated.h"

UCLASS()
class DUNGEONZERO_API ADZClockActor : public AActor
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	UFUNCTION()
	void OnRep_TimeLeft();
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
public:
	
	ADZClockActor();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 컴포넌트
	
	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트
	//━━━━━━━━━━━━━━━━━━━━
    
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	TObjectPtr<USceneComponent> RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	TObjectPtr<UStaticMeshComponent> BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	TObjectPtr<UStaticMeshComponent> HourHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	TObjectPtr<UStaticMeshComponent> MinuteHandMesh;

#pragma endregion	
//======================================================================================================================	
#pragma region TimeAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// TimeAPI
	//━━━━━━━━━━━━━━━━━━━━

protected:
	
	// 메시지 수신 함수
	void OnTimeReduceReceived(FGameplayTag Channel, const FDZTimeMSG& Payload);
	void OnTimeOverReceived(FGameplayTag Channel, const FDZTimeMSG& Payload);
	
	// 시계 바늘 업데이트 로직
	void UpdateClockVisuals();
    
	// 종소리 체크 및 실행 로직
	void CheckAndPlayChime(float NewTime);

	// 실제 종소리 재생 카운트 함수
	void PlayChimeSound(int32 Count);
	
	// 실제 소리를 하나씩 재생할 함수
	void PlaySingleChime();
protected:

	// 구독 핸들
	FGameplayMessageListenerHandle TimeReduceListenerHandle;
	FGameplayMessageListenerHandle TimeOverListenerHandle;
	
#pragma endregion
//======================================================================================================================	
#pragma region Data		

	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
protected:

	// 종소리
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	TObjectPtr<USoundBase> ChimeSound = nullptr;
	
	// 종소리 타이머 핸들
	FTimerHandle ChimeTimerHandle;
	
	// 종소리 간격 (에디터에서 조절 가능하게)
	UPROPERTY(EditAnywhere, Category = "DZ")
	float ChimeInterval = 1.0f;
	
	// 남은 종소리 횟수 카운터
	int32 RemainingChimesToPlay = 0;
	
	// 타겟 스테이지 레벨 (처음 시간 알기 위함)
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	int32 TargetRoomLevel = -1;
	
	// 마지막으로 종이 울린 분(Minute) 체크용
	int32 LastChimedMinute = -1;

	// 데이터에서 가져올 초기 전체 시간
	float TotalDuration = 0.0f;

	// 남은 시간 
	UPROPERTY(ReplicatedUsing = OnRep_TimeLeft, VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	float TimeLeft = 0.0f;
	
	// 디버그 on off
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	bool bWantPrintDebug = false;
	
	
#pragma endregion
//======================================================================================================================	
};
