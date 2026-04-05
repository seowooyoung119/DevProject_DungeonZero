// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyEyeLight.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyEyeLight : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	
	ADZGCN_AnomalyEyeLight();
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 컴포넌트_및_데이터

	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트_및_데이터
	//━━━━━━━━━━━━━━━━━━━━	
protected:
	
	// 실제 위치를 고정해줄 가상 루트
	UPROPERTY(VisibleAnywhere, Category = "DZ")
	TObjectPtr<USceneComponent> SceneRoot;
	
	UPROPERTY(VisibleAnywhere, Category = "DZ")
	TObjectPtr<UStaticMeshComponent> Eye = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FName EyeLightTargetMeshTag = FName(TEXT(""));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FName AttachSocketName = FName(TEXT(""));
	
#pragma endregion
//======================================================================================================================	
#pragma region 눈알

	//━━━━━━━━━━━━━━━━━━━━
	// 눈알
	//━━━━━━━━━━━━━━━━━━━━	
protected:
	
	// 로컬 플레이어 감지용 볼륨
	UPROPERTY(VisibleAnywhere, Category = "DZ")
	TObjectPtr<UBoxComponent> DetectVolume = nullptr;

	// 플레이어 감지 시 호출될 함수
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// 현재 추적 중인 로컬 플레이어 폰
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TObjectPtr<APawn> TrackedPlayer = nullptr;

	// 눈알이 회전할 때의 부드러움 정도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	float RotationInterpolationSpeed = 5.0f;
	
#pragma endregion
//======================================================================================================================	
	
};
