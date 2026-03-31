// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"


// 게임 플레이에서 어떤 역할을 맡고 있는지 알려주는 enum
UENUM(BlueprintType)
enum class EDZPlayRole : uint8
{
	None		UMETA(DisplayName = "None"),
	Player		UMETA(DisplayName = "Player"),
	Monster		UMETA(DisplayName = "Monster"),
	Item		UMETA(DisplayName = "Item"),
	Anomaly		UMETA(DisplayName = "Anomaly"),
};
