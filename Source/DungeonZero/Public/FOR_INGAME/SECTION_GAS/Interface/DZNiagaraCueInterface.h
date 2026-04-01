// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZNiagaraCueData.h"
#include "DZNiagaraCueInterface.generated.h"

UINTERFACE()
class UDZNiagaraCueInterface : public UInterface
{
	GENERATED_BODY()
};

class DUNGEONZERO_API IDZNiagaraCueInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Cue")
	bool GetNiagaraCueData(const FGameplayTag& CueTag, FDZNiagaraCueData& OutData);
};
