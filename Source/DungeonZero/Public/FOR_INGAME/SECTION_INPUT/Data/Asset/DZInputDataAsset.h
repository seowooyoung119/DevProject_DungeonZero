// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DZInputDataAsset.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
		
public:
	
//======================================================================================================================
#pragma region 기본_움직임
	
	// 기본 IMC 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputMappingContext> DefaultMovementIMC = nullptr;

	// WASD 움직임
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_Move = nullptr;

	// 시야 회전 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_Look = nullptr;

	// 점프
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_Jump = nullptr;
	
#pragma endregion
//======================================================================================================================
#pragma region 상호작용_관련
	
	// 상호작용 IMC
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputMappingContext> InteractIMC = nullptr;

	// 왼쪽 마우스 상호작용 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_InteractByLeftClick = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
