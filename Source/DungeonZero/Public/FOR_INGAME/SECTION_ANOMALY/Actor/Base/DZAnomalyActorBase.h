// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
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
	
	// GAS 관련 초기화
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UAbilitySystemComponent> AnomalyAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " DZ")
	TObjectPtr<UDZGiveGAGEDataAsset> BaseGAGEData = nullptr;
	
#pragma endregion
//======================================================================================================================		
};
