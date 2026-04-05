// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZItemRuntimeData.h"
#include "DZInventoryCompActionInterface.generated.h"


// This class does not need to be modified.
UINTERFACE()
class UDZInventoryCompActionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *  인벤토리 외부 API 설계도
 */
class DUNGEONZERO_API IDZInventoryCompActionInterface
{
	GENERATED_BODY()
	
public:
	// 아이템 습득
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Inventory")
	bool AddItemToInventory(FDZItemRuntimeData InItemRuntimeData);
    
	// 아이템 제거
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Inventory")
	bool RemoveItemFromInventory(int32 TargetSlotIndex, int32 DeleteCount);
    
	// 아이템 드랍
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Inventory")
	bool DropItemToFromInventory(int32 TargetSlotIndex, int32 DeleteCount);
    
	// 아이템 스왑
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Inventory")
	bool SwapItemFromThisInventoryToAnotherInventory(FDZItemRuntimeData InItemRuntimeData);
	
};
