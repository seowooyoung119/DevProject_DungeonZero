// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "DZAICharacterBase.generated.h"

class UDZGiveGAGEDataAsset;
class UDZAttributeSet;

UCLASS()
class DUNGEONZERO_API ADZAICharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZAICharacterBase();
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================	
#pragma region GAS
	//━━━━━━━━━━━━━━━━━━━━
	// GAS
	//━━━━━━━━━━━━━━━━━━━━

protected:
	// IAbilitySystemInterface ~ 
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	// ~ IAbilitySystemInterface	
	
protected:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DZ")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DZ")
	TObjectPtr<UDZAttributeSet> AttributeSet = nullptr;
	
	// GAS 관련 초기화
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DZ")
	TObjectPtr<UDZGiveGAGEDataAsset> BaseGAGEData = nullptr;
	
#pragma endregion
//======================================================================================================================		
	
};
