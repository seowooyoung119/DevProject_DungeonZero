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
	
	// 오른족 마우스 상호작용
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_InteractByRightClick = nullptr;
	
	// 특수 상호작용 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_SpecialInteract = nullptr;
	
	// 아이템 줍기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_PickUpItem = nullptr;
	
	// 아이템 버리기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_DropItem = nullptr;
	
#pragma endregion
//======================================================================================================================
#pragma region 핫키
	
	// 핫키 IMC
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputMappingContext> HotKeyIMC = nullptr;
	
	// 핫키 상호작용 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_HotkeyInteract1 = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_HotkeyInteract2 = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_HotkeyInteract3 = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<UInputAction> IA_HotkeyInteract4 = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")	
	TObjectPtr<UInputAction> IA_HotkeyInteract5 = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")	
	TObjectPtr<UInputAction> IA_HotkeyInteract6 = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")	
	TObjectPtr<UInputAction> IA_HotkeyInteract7 = nullptr;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")	
	TObjectPtr<UInputAction> IA_HotkeyInteract8 = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TS | Input")	
	TObjectPtr<UInputAction> IA_HotkeyInteract9 = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
