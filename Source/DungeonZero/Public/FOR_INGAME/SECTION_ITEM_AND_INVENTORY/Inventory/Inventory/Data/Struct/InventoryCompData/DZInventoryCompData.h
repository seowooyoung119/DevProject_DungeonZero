// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Enum/InventoryType/DZInventoryCompType.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Struct/InventorySlot/DZInventorySlotData.h"
#include "DZInventoryCompData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZInventoryCompData
{
	GENERATED_BODY()
	
	// 인벤토리 타입
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "DZ | Inventory")
	EDZInventoryCompType InventoryType = EDZInventoryCompType::PlayerHotKey;
	
	// 슬롯 배열 (Save On)
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "DZ | Inventory")
	TArray<FDZInventorySlotData> InventoryDataArray = {};
};
