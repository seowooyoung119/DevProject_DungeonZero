// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZAnomalyGrantData.h"
#include "DZAnomalyGrantDataAsset.generated.h"

UCLASS()
class DUNGEONZERO_API UDZAnomalyGrantDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	TArray<FDZAnomalyGrantData> GrantedAbilities; 
};
