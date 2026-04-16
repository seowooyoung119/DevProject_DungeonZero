// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"
#include "FOR_INGAME/SECTION_ANOMALY/Interface/DZAnomalySealAdditionalFunction.h"
#include "FOR_INGAME/SECTION_GAS/Interface/DZCueVIsualInterface.h"
#include "DZAnomalyActorBase.generated.h"

class UDZAnomalyGrantDataAsset;
class UAbilitySystemComponent;

UCLASS()
class DUNGEONZERO_API ADZAnomalyActorBase : public AActor, public IAbilitySystemInterface, 
public IDZCommonPlayRoleInterface, public IDZCueVIsualInterface, public IDZAnomalySealAdditionalFunction
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

public:
	ADZAnomalyActorBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion
//======================================================================================================================
#pragma region 게터

	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	
public:
	virtual UPrimitiveComponent* GetAnomalyPrimitiveComponent() { return nullptr; }

#pragma endregion
//======================================================================================================================
#pragma region 컴포넌트

	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트
	//━━━━━━━━━━━━━━━━━━━━	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | AnomalyActor")
	TObjectPtr<UAbilitySystemComponent> AnomalyAbilitySystemComponent = nullptr;
#pragma endregion
//======================================================================================================================		
#pragma region 플레이롤

	//━━━━━━━━━━━━━━━━━━━━
	// 플레이롤
	//━━━━━━━━━━━━━━━━━━━━	

public:
	// IDZCommonPlayRoleInterface ~ 
	FORCEINLINE virtual EDZPlayRole GetPlayRole_Implementation() override { return PlayRole; }
	// ~ IDZCommonInteractInterface

protected:
	// 롤 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | AnomalyActor | PlayRole")
	EDZPlayRole PlayRole = EDZPlayRole::Anomaly;
#pragma endregion
//======================================================================================================================		
#pragma region 어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리
	//━━━━━━━━━━━━━━━━━━━━	

public:
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AnomalyAbilitySystemComponent;
	};
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	void SetAnomalyScale(float InScale);

protected:
	// 어빌리티 랜덤 선택 및 부여
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC);
	// 어빌리티 실행
	virtual void ActivateAnomaly_internal(UAbilitySystemComponent* InASC);
	// 스케일 변경 복제
	UFUNCTION()
	void OnRep_AnomalyScale();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " DZ | AnomalyActor")
	TObjectPtr<UDZAnomalyGrantDataAsset> AnomalyGrantData = nullptr;

	// 부여된 어빌리티 핸들 저장
	UPROPERTY()
	FGameplayAbilitySpecHandle AnomalyAbilitySpecHandle;
	// 어노말리 스케일
	UPROPERTY(ReplicatedUsing = OnRep_AnomalyScale)
	float ReplicatedAnomalyScale = 1.0f;

#pragma endregion
//======================================================================================================================	
#pragma region Cue Visual Interface

	//━━━━━━━━━━━━━━━━━━━━
	// Cue Visual Interface
	//━━━━━━━━━━━━━━━━━━━━	

public:
	UFUNCTION(BlueprintCallable, Category = "DZ | AnomalyActor | CueVisual")
	virtual bool GetLoopSoundCueData(const FGameplayTag& GATag, FDZLoopSoundCueData& OutData) override;
	UFUNCTION(BlueprintCallable, Category = "DZ | AnomalyActor | CueVisual")
	virtual bool GetNiagaraCueData(const FGameplayTag& GATag, TArray<FDZNiagaraCueData>& OutData) override;
	UFUNCTION(BlueprintCallable, Category = "DZ | AnomalyActor | CueVisual")
	virtual bool GetDecalCueData(const FGameplayTag& GATag, TArray<FDZDecalCueData>& OutData) override;
	UFUNCTION(BlueprintCallable, Category = "DZ | AnomalyActor | CueVisual")
	virtual bool GetMaterialCueData(const FGameplayTag& GATag, TArray<FDZMaterialCueData>& OutData) override;
	UFUNCTION(BlueprintCallable, Category = "DZ | AnomalyActor | CueVisual")
	virtual void SetOriginalMaterial(const FGameplayTag& GATag) override;
	UFUNCTION(BlueprintCallable, Category = "DZ | AnomalyActor | CueVisual")
	virtual void SetRecieveDecals(bool bEnable) override;

protected:
	// 소켓별 나이아가라 이펙트 리스트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | AnomalyActor | CueVisual")
	TMap<FGameplayTag, FDZNiagaraCueDataArray> NiagaraMap;

	// 소켓별 데칼 리스트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | AnomalyActor | CueVisual")
	TMap<FGameplayTag, FDZDecalCueDataArray> DecalMap;

	// 메시 머티리얼 오버라이드 리스트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | AnomalyActor | CueVisual")
	TMap<FGameplayTag, FDZMaterialCueDataArray> MaterialMap;
	
	// 루프 사운드 리스트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | AnomalyActor | CueVisual")
	TMap<FGameplayTag, FDZLoopSoundCueData> LoopSoundMap;

#pragma endregion
//======================================================================================================================
#pragma region 트리거

	//━━━━━━━━━━━━━━━━━━━━
	// 트리거
	//━━━━━━━━━━━━━━━━━━━━	
protected:
	bool bActivateOnTrigger = false;
	bool bDeactivateOnTrigger = false;
#pragma endregion
//======================================================================================================================
#pragma region 어노말리_엔딩_펑션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리 엔딩 펑션
	//━━━━━━━━━━━━━━━━━━━━	
public:
	// GAS로 하기 비효율적이거나 액터와 연관이 되어 있을 경우 이 인터페이스의 API를 상속하여 로직을 추가한 뒤 GAS의 EndAbility 에서 인터페이스 호출 
	virtual void AnomalySealAdditionalFunction_Implementation() override { return; };
	
#pragma endregion
//======================================================================================================================	
};
