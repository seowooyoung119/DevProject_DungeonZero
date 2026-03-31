// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Struct/InventoryCompData/DZInventoryCompData.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZItemRuntimeData.h"
#include "DZItemCheckLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UTSItemCheckLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	// 아이템이 유효한가?
	static bool IsThisItemValid_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData);
	
	// 스택이 가능한 아이템인가?
	static bool IsThisITemCanStack_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData);

	// 최대 스택이 몇인가?
	static int32 GetMaxStackSize_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData);

	// 이 아이템은 인벤토리에 들엉올 수 있는가? 
	static bool IsThisItemCanPlaceInThisInventory_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData, FDZInventoryCompData& InInventoryData);
	
	// 같은 아이템인가?
	static bool IsThisSameItem_Lib(FDZItemRuntimeData InFromSlotItemData, FDZItemRuntimeData InItemRuntimeData);
};
