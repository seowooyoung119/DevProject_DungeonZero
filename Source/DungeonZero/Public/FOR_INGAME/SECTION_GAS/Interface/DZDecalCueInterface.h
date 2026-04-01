// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZDecalCueData.h"
#include "UObject/Interface.h"
#include "DZDecalCueInterface.generated.h"

UINTERFACE()
class UDZDecalCueInterface : public UInterface
{
	GENERATED_BODY()
};

class DUNGEONZERO_API IDZDecalCueInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Cue")
	bool GetDecalCueData(const FGameplayTag& CueTag, FDZDecalCueData& OutData);
};
