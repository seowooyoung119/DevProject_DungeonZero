// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DZInventoryOwnerActionInterface.generated.h"

class UDZHotKeyInventoryComponent;

// This class does not need to be modified.
UINTERFACE()
class UDZInventoryOwnerActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZInventoryOwnerActionInterface
{
	GENERATED_BODY()

public:
	
	// 핫키 게터
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Inventory")
	UDZHotKeyInventoryComponent* GetHotKeyComponent();

};
