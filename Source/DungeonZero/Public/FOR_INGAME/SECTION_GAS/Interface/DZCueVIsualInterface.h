// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZDecalCueData.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZMaterialCueData.h"
#include "UObject/Interface.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZNiagaraCueData.h"

#include "DZCueVIsualInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDZCueVIsualInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZCueVIsualInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Cue")
	bool GetNiagaraCueData(const FGameplayTag& CueTag, FDZNiagaraCueData& OutData);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Cue")
	bool GetDecalCueData(const FGameplayTag& CueTag, FDZDecalCueData& OutData);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Cue")
	bool GetMaterialCueData(const FGameplayTag& CueTag, FDZMaterialCueData& OutData);
};
