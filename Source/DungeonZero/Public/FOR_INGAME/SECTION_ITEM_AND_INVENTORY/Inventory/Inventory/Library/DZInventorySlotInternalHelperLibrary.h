// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Struct/InventorySlot/DZInventorySlotData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZInventorySlotInternalHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInventorySlotInternalHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	// 이 슬롯이 비었는가?
	static bool IsSlotEmpty_Lib(FDZInventorySlotData& InInventorySlotData);
	
};
