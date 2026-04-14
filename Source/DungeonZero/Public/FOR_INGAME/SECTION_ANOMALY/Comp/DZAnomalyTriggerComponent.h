// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Components/SceneComponent.h"
#include "DZAnomalyTriggerComponent.generated.h"


class UBoxComponent;
class UAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZAnomalyTriggerComponent : public USceneComponent
{
	GENERATED_BODY()

	//======================================================================================================================
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━

public:
	UDZAnomalyTriggerComponent();

#pragma endregion
	//======================================================================================================================
	
#pragma region 컴포넌트

	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트
	//━━━━━━━━━━━━━━━━━━━━

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | TriggerComponent")
	TObjectPtr<UBoxComponent> TriggerBox;

#pragma endregion
	//======================================================================================================================
#pragma region 트리거

	//━━━━━━━━━━━━━━━━━━━━
	// 트리거
	//━━━━━━━━━━━━━━━━━━━━

public:
	// 트리거 설정 및 오버랩 바인딩 (bActivateOnTrigger == false 시 콜리전 비활성화)
	void SetupTrigger(UAbilitySystemComponent* InASC, const FGameplayAbilitySpecHandle& InHandle,
					  bool bInActivateOnTrigger, bool bInDeactivateOnTrigger);

private:
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
							   bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TWeakObjectPtr<UAbilitySystemComponent> WeakASC;
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	bool bActivateOnTrigger = false;
	bool bDeactivateOnTrigger = false;
	int32 OverlappingPlayers = 0;

#pragma endregion
	//======================================================================================================================
};
