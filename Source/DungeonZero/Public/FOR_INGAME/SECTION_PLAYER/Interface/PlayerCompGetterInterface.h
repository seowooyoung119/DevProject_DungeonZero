// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerCompGetterInterface.generated.h"

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
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZInteractComponent* GetDZInteractComponent();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZHotKeyInventoryComponent* GetDZHotKeyInventoryComponent();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | PlayerCompGetter")
	UDZHotKeyEquipVisualComponent* GetDZHotKeyEquipVisualComponent();
	
};
