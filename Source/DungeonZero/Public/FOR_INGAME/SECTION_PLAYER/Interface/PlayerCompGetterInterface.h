// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerCompGetterInterface.generated.h"

class UDZBodyEquipVisualComponent;
class UDZBodyEquipInventoryComponent;
class UDZHotKeyEquipVisualComponent;
class UDZHotKeyInventoryComponent;
class UDZInteractComponent;
// This class does not need to be modified.
UINTERFACE()
class UPlayerCompGetterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IPlayerCompGetterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// 인터렉트 컴포넌트 게터 (라인 트레이스로 현재 보는 액터를 캐싱하는 컴포넌트임) 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZInteractComponent* GetDZInteractComponent();
	
	// 핫키 인벤토리
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZHotKeyInventoryComponent* GetDZHotKeyInventoryComponent();
	
	// 핫키 인벤토리 비주얼
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZHotKeyEquipVisualComponent* GetDZHotKeyEquipVisualComponent();
	
	// 장비 (손, 몸, 머리 등등) 인벤토리 (핫키는 제외)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZBodyEquipInventoryComponent* GetBodyEquipInventoryComponent();
	
	// 장비 인벤토리 비주얼 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZBodyEquipVisualComponent* GetBodyEquipVisualComponent();
	
};
