// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZTimeMSG.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/EndingMSG.h"
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

	UFUNCTION()
	void OnRep_CallPlayChimeSoundToClient(); // 종소리 사운드 동기화용 호출

	UFUNCTION()
	void OnRep_CallPlayEndingSoundToClient(); // 엔딩 사운드 복제용 호출 
	
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
	void OnTimeResetReceived(FGameplayTag Channel, const FDZTimeMSG& Payload);
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
	FGameplayMessageListenerHandle TimeResetListenerHandle;
	FGameplayMessageListenerHandle TimeReduceListenerHandle;
	FGameplayMessageListenerHandle TimeOverListenerHandle;
	
#pragma endregion
//======================================================================================================================
#pragma region EndingAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// EndingAPI
	//━━━━━━━━━━━━━━━━━━━━	

protected:
	// 엔딩 수신 함수
	void OnEndingReceived(FGameplayTag Channel, const FDZEndingMSG& Payload);
	
	// 엔딩 종소리
	void PlayEndingChime();
	
	// 구독 핸들
	FGameplayMessageListenerHandle EndingListenerHandle;
	
#pragma endregion
//======================================================================================================================	
#pragma region Data		

	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
protected:

	//-------------------
	// 종소리
	//-------------------
	
	// 종소리
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	TObjectPtr<USoundBase> ChimeSound = nullptr;
	
	// 엔딩 시 날 종소리
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	TObjectPtr<USoundBase> EndingChimeSound = nullptr;

	//-------------------
	// 종소리 옵션
	//-------------------
	
	// 종소리 간격 (에디터에서 조절 가능하게)
	UPROPERTY(EditAnywhere, Category = "DZ")
	float ChimeInterval = 1.0f;
	
	//-------------------
	// 타이머
	//-------------------
	
	// 종소리 타이머 핸들
	FTimerHandle ChimeTimerHandle;
	FTimerHandle EndingTimerHandle;
	
	//-------------------
	// 관리용 데이터 (서버만 사용)
	//-------------------
	
	int32 LocalLastChimedMinute = -1;	// 클라이언트의 이전 종소리 단계 기록 (중복 재생 방지)
	int32 RemainingChimesToPlay = 0;	// 남은 종소리 횟수 카운터
	int32 LastChimedMinute = -1;		// 마지막으로 종이 울린 분(Minute) 체크용

	//-------------------
	// 관리용 데이터 (서버 및 클라이언트 사용)
	//-------------------

	// 데이터에서 가져올 초기 전체 시간 (복제하여 시침 회전 값 계산 때 사용)
	UPROPERTY(Replicated)
	float TotalDuration = 0.0f;

	// 남은 시간 (onRep 에서 시침 회전 호출) 
	UPROPERTY(ReplicatedUsing = OnRep_TimeLeft)
	float TimeLeft = 0.0f;
	
	//-------------------
	// 동기화용 데이터
	//-------------------
	
	// NOTE :: 서버에서 계산한 값대로 사운드 호출을 하기위한 변수이므로 아무 의미 없이 그냥 증가 시킴
	UPROPERTY(ReplicatedUsing = OnRep_CallPlayChimeSoundToClient) int32 CallPlayChimeSoundToClient = 0;
	UPROPERTY(ReplicatedUsing = OnRep_CallPlayEndingSoundToClient) int32 CallPlayEndingSoundToClient = 0;
	
#pragma endregion
//======================================================================================================================	
};
