// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Interface/ForOwner/DZInventoryOwnerActionInterface.h"
#include "DZPlayerCharacter.generated.h"

class UDZGiveGAGEDataAsset;
class UDZInteractComponent;
class UCameraComponent;
class USpringArmComponent;
class UDZInputHandleComponent;

UCLASS()
class DUNGEONZERO_API ADZPlayerCharacter : public ACharacter, public IAbilitySystemInterface, public IDZInventoryOwnerActionInterface, public IPlayerCompGetterInterface
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	virtual UDZHotKeyInventoryComponent* GetDZHotKeyInventoryComponent_Implementation() override { return HotKeyInventoryComponent; };
	virtual UDZInteractComponent* GetDZInteractComponent_Implementation() override { return InteractComponent; };
	virtual UDZHotKeyEquipVisualComponent* GetDZHotKeyEquipVisualComponent_Implementation() override { return HotKeyEquipVisualComponent; } 
	
#pragma endregion
//======================================================================================================================	
#pragma region OnRep
	
	//━━━━━━━━━━━━━━━━━━━━
	// OnRep
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	
	UFUNCTION() void OnRep_JobRole();

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
	
	
public:
	ADZPlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
#pragma endregion
//======================================================================================================================	
#pragma region GAS_섹션
	//━━━━━━━━━━━━━━━━━━━━
	// GAS
	//━━━━━━━━━━━━━━━━━━━━

protected:
	// IAbilitySystemInterface ~ 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;;
	// ~ IAbilitySystemInterface
	
	// GAS 관련 초기화
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " DZ")
	TObjectPtr<UDZGiveGAGEDataAsset> BaseGAGEData = nullptr;
	
#pragma endregion
//======================================================================================================================
#pragma region 인터렉트_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_섹션
	//━━━━━━━━━━━━━━━━━━━━
		
protected:
	// 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UDZInteractComponent> InteractComponent;
	
#pragma endregion
//======================================================================================================================
#pragma region 입력_섹션
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 입력_섹션
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UDZInputHandleComponent> InputHandleComponent = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region 카메라와_스프링암
	
	//━━━━━━━━━━━━━━━━━━━━
	// 카메라와_스프링암
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region 인벤토리
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인벤토리
	//━━━━━━━━━━━━━━━━━━━━	

public:
	// IDZInventoryOwnerActionInterface~ 
	virtual UDZHotKeyInventoryComponent* GetHotKeyComponent_Implementation() override { return HotKeyInventoryComponent; };
	// ~ IDZInventoryOwnerActionInterface
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UDZHotKeyInventoryComponent> HotKeyInventoryComponent = nullptr;

#pragma endregion
//======================================================================================================================	
#pragma region 인벤토리_비쥬얼
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인벤토리_비쥬얼
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UDZHotKeyEquipVisualComponent> HotKeyEquipVisualComponent = nullptr;

#pragma endregion
//======================================================================================================================	
};
