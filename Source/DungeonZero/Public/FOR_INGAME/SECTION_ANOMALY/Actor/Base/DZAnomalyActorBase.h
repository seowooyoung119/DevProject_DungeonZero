// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "DZAnomalyActorBase.generated.h"

class UDZGiveGAGEDataAsset;
class UAbilitySystemComponent;

UCLASS()
class DUNGEONZERO_API ADZAnomalyActorBase : public AActor, public IAbilitySystemInterface
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
	
#pragma endregion
//======================================================================================================================		
#pragma region 어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AnomalyAbilitySystemComponent; };
	
protected:
	
	// 어빌리티 랜덤 선택 및 부여
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC);
	// 어빌리티 실행
	virtual void ActivateAnomaly_internal(UAbilitySystemComponent* InASC);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UAbilitySystemComponent> AnomalyAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " DZ")
	TObjectPtr<UDZGiveGAGEDataAsset> BaseGAGEData = nullptr;
	
	// 부여된 어빌리티 핸들 저장
	UPROPERTY()
	FGameplayAbilitySpecHandle AnomalyAbilitySpecHandle;
	
#pragma endregion
//======================================================================================================================		
};
