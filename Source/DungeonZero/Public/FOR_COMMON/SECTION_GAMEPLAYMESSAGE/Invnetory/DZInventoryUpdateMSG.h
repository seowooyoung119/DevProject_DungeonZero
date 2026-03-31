// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Enum/InventoryType/DZInventoryCompType.h"
#include "DZInventoryUpdateMSG.generated.h"

class UDZInventoryMasterComponent;

USTRUCT(BlueprintType)
struct FDZInventoryUpdateMessage
{
	GENERATED_BODY()

	// 어떤 인벤토리가 변했는지 구별하기 위한 태그 (예: Inventory.Slot.Updated)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EDZInventoryCompType ChangeInventoryType = EDZInventoryCompType::None;
	
	// 인벤토리 포인터 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDZInventoryMasterComponent* InventoryComp = nullptr;
	
};