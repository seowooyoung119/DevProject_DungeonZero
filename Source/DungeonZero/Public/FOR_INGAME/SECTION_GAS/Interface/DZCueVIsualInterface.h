// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZDecalCueData.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZLoopSoundCueData.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZMaterialCueData.h"
#include "UObject/Interface.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZNiagaraCueData.h"
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
	virtual bool GetLoopSoundCueData(const FGameplayTag& GATag, FDZLoopSoundCueData& OutData);
	
	UFUNCTION(BlueprintCallable, Category = "DZ | Cue")
	virtual bool GetNiagaraCueData(const FGameplayTag& GATag, TArray<FDZNiagaraCueData>& OutData);
	
	UFUNCTION(BlueprintCallable, Category = "DZ | Cue")
	virtual bool GetDecalCueData(const FGameplayTag& GATag, TArray<FDZDecalCueData>& OutData);
	
	UFUNCTION(BlueprintCallable, Category = "DZ | Cue")
	virtual bool GetMaterialCueData(const FGameplayTag& GATag, TArray<FDZMaterialCueData>& OutData);
	
	UFUNCTION(BlueprintCallable, Category = "DZ | Cue")
	virtual void SetRecieveDecals(bool bEnable);
};
