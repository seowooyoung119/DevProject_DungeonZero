// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "DZInventorySlotType.generated.h"

/**
 * 인벤토리의 슬롯이 어떤 타입인지 알려주는 enum
 */
UENUM(BlueprintType)
enum class EDZInventorySlotType : uint8
{
	None			UMETA(DisplayName = "None"),
	Common			UMETA(DisplayName = "Common"),
};
