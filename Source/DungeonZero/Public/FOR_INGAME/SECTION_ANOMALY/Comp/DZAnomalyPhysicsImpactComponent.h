// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZPhysicsImpactData.h"
#include "DZAnomalyPhysicsImpactComponent.generated.h"


class UDZAnomalySoundDataAsset;
class UAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZAnomalyPhysicsImpactComponent : public UActorComponent
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━		
	
public:
	UDZAnomalyPhysicsImpactComponent();
	
protected:
	virtual void BeginPlay() override;
#pragma endregion
//======================================================================================================================
#pragma region 게터

	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

public:
	// 어빌리티 태그 → 임팩트 이펙트 데이터
	bool GetPhysicsImpactData(const FGameplayTag& GATag, FDZPhysicsImpactData& OutData);
	// 표면별 임팩트 사운드 
	TObjectPtr<USoundBase> GetImpactSound(const FHitResult& Hit);
	// OwnerPrimitiveComponent
	TObjectPtr<UPrimitiveComponent> GetOwnerPrimitiveComponent() const { return OwnerPrimitiveComponent; }

#pragma endregion
//======================================================================================================================
#pragma region 피직스_임팩트

	//━━━━━━━━━━━━━━━━━━━━
	// 피직스_임팩트
	//━━━━━━━━━━━━━━━━━━━━

public:
	// 어빌리티에서 피직스 활성화 시 호출
	void ActivatePhysics_internal(FGameplayTagContainer InAbilityTags);

private:
	UFUNCTION()
	void OnHitGround_internal(
		UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit);
	UFUNCTION()
	void FinishPhysicsImpact();

#pragma endregion
//======================================================================================================================
#pragma region 데이터

	//━━━━━━━━━━━━━━━━━━━━
	// 데이터
	//━━━━━━━━━━━━━━━━━━━━

public:
	// 표면별 임팩트 사운드 데이터 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | PhysicsImpact")
	TObjectPtr<UDZAnomalySoundDataAsset> ImpactSoundDataAsset;
	// 어빌리티 태그 → 임팩트 이펙트 데이터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | PhysicsImpact")
	TMap<FGameplayTag, FDZPhysicsImpactData> ImpactDataMap;

#pragma endregion
//======================================================================================================================
#pragma region 내부_상태

	//━━━━━━━━━━━━━━━━━━━━
	// 내부_상태
	//━━━━━━━━━━━━━━━━━━━━

private:
	// ActivatePhysics 호출 시 저장, OnHitGround에서 TMap 조회에 사용
	FGameplayTagContainer PendingAbilityTags;

	// BeginPlay에서 오너의 GetAnomalyPrimitiveComponent()로 캐싱
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> OwnerPrimitiveComponent = nullptr;

	// BeginPlay에서 IAbilitySystemInterface로 캐싱
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> OwnerASC = nullptr;

#pragma endregion
	//======================================================================================================================

};
