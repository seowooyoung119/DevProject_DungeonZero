// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "DZInventoryCompType.generated.h"

/**
 *  인벤토리가 어떤 타입인지 알려주는 enum
 */
UENUM(BlueprintType)
enum class EDZInventoryCompType : uint8
{
	None		UMETA(DisplayName = "None"),
	
	// 플레이어
	PlayerHotKey	UMETA(DisplayName = "HotKey"),
	PlayerBody		UMETA(DisplayName = "Body"),
};
