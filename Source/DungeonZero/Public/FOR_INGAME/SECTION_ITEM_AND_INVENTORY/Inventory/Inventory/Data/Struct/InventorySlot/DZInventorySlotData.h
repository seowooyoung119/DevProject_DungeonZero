// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Enum/InventorySlotType/DZInventorySlotType.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZItemRuntimeData.h"
#include "DZInventorySlotData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZInventorySlotData
{
	GENERATED_BODY()
	
	// 인벤토리 슬롯 타입 
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "TS | Inventory")
	EDZInventorySlotType InventorySlotType = EDZInventorySlotType::Common;
	
	// 아이템 데이터 
	UPROPERTY(SaveGame, EditAnywhere, BlueprintReadWrite, Category = "TS | Inventory")
	FDZItemRuntimeData ItemData;
	
};
