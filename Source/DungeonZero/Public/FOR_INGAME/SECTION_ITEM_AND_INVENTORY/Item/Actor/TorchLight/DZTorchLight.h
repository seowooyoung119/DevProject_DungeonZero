// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/StaticMeshItem/DZStaticMeshItem.h"
#include "DZTorchLight.generated.h"

class UAudioComponent;
class UWidgetComponent;
class UNiagaraComponent;
class UPointLightComponent;

UCLASS()
class DUNGEONZERO_API ADZTorchLight : public ADZStaticMeshItem
{
	GENERATED_BODY()

//======================================================================================================================
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━
public:
	ADZTorchLight();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion
//======================================================================================================================
#pragma region 컴포넌트

	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트
	//━━━━━━━━━━━━━━━━━━━━
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | TorchLight")
	TObjectPtr<UAudioComponent> Audio = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | TorchLight")
	TObjectPtr<UNiagaraComponent> Niagara = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | TorchLight")
	TObjectPtr<UPointLightComponent> PointLight = nullptr;

#pragma endregion
//======================================================================================================================
#pragma region 빛_감소_타이머

	//━━━━━━━━━━━━━━━━━━━━
	// 빛 감소 타이머
	//━━━━━━━━━━━━━━━━━━━━
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | TorchLight")
	float InitialIntensity = 5000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | TorchLight")
	float IntensityDecreasePerTick = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | TorchLight")
	FName NiagaraParameterName = "FireScale";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | TorchLight")
	float NiagaraInitialFireScale = 1.f;

private:
	FTimerHandle LightDecreaseTimerHandle;

	void LightDecreaseTick_internal();
	void StartLightDecreaseTimer();

#pragma endregion
//======================================================================================================================#pragma region 빛_감소_타이머
#pragma region 횃불_충전

	//━━━━━━━━━━━━━━━━━━━━
	// 횃불 충전
	//━━━━━━━━━━━━━━━━━━━━
public:
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "DZ | TorchLight")
	void TorchCharge();
	UFUNCTION(BlueprintCallable, Category = "DZ | TorchLight")
	void SetTorchActivated(bool bIsActive);
#pragma endregion
//======================================================================================================================
};
