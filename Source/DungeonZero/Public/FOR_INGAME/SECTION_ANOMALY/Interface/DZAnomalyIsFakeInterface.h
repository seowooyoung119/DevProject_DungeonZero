// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DZAnomalyIsFakeInterface.generated.h"

UINTERFACE()
class UDZAnomalyIsFakeInterface : public UInterface
{
	GENERATED_BODY()
};

class DUNGEONZERO_API IDZAnomalyIsFakeInterface
{
	GENERATED_BODY()

public:
	virtual bool IsFakeAnomaly() const = 0;
};
