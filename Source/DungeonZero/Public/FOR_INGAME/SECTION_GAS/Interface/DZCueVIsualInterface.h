// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZDecalCueData.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZMaterialCueData.h"
#include "UObject/Interface.h"
#include "FOR_INGAME/SECTION_GAS/Data/Cue/DZNiagaraCueData.h"
#include "DZCueVIsualInterface.generated.h"

UINTERFACE(NotBlueprintable)
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
	UFUNCTION(BlueprintCallable, Category = "DZ | Cue")
	virtual bool GetNiagaraCueData(const FGameplayTag& GATag, TArray<FDZNiagaraCueData>& OutData);
	
	UFUNCTION(BlueprintCallable, Category = "DZ | Cue")
	virtual bool GetDecalCueData(const FGameplayTag& GATag, TArray<FDZDecalCueData>& OutData);
	
	UFUNCTION(BlueprintCallable, Category = "DZ | Cue")
	virtual bool GetMaterialCueData(const FGameplayTag& GATag, TArray<FDZMaterialCueData>& OutData);
};
