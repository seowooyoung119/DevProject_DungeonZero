// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "DZPlayerState.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	ADZPlayerState();
	
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
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " DZ")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
#pragma endregion
//======================================================================================================================	
	
};
