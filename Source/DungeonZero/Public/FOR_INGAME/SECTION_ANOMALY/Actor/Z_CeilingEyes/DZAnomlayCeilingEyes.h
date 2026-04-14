// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "DZAnomlayCeilingEyes.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

// 각 눈알의 개별 데이터를 관리하기 위한 구조체
USTRUCT(BlueprintType)
struct FEyeInstanceData
{
    GENERATED_BODY()

    UPROPERTY()
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY()
    float IndividualSpeed = 0.0f;
};

UCLASS()
class DUNGEONZERO_API ADZAnomalyCeilingEyes : public ADZAnomalyActorBase
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	
	ADZAnomalyCeilingEyes();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 눈알

	//━━━━━━━━━━━━━━━━━━━━
	// 눈알
	//━━━━━━━━━━━━━━━━━━━━	
protected:
	// --- 에디터 설정 ---
    
	// 에디터에서 눈알 메쉬들을 담아줄 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ|Eyes")
	TArray<TObjectPtr<UStaticMeshComponent>> EyeComponents;

	// 랜덤 속도의 최소/최대 범위
	UPROPERTY(EditAnywhere, Category = "DZ|Eyes")
	float MinRotationSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "DZ|Eyes")
	float MaxRotationSpeed = 8.0f;
	
	// 눈알 메쉬의 기본 앞방향을 보정하기 위한 오프셋
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ|Eyes")
    FRotator EyeRotationOffset = FRotator(0.0f, 90.0f, 0.0f); 
    
	// --- 런타임 데이터 ---

	// 감지 볼륨
	UPROPERTY(VisibleAnywhere, Category = "DZ")
	TObjectPtr<UBoxComponent> DetectVolume;

	// 실제 동작 시 사용할 캐싱 데이터
	UPROPERTY()
	TArray<FEyeInstanceData> EyeInstances;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TObjectPtr<APawn> TrackedPlayer = nullptr;
	
	// 트리거 함수
	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion
//======================================================================================================================
};
