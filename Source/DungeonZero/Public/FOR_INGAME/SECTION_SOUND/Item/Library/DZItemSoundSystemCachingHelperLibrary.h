// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FOR_INGAME/SECTION_SOUND/Item/Data/Table/DZItemDropSoundTable.h"
#include "FOR_INGAME/SECTION_SOUND/Item/Data/Table/DZItemPickUpSoundTable.h"
#include "DZItemSoundSystemCachingHelperLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZItemSoundSystemCachingHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	static void CacheItemPickUpSoundDataTable_Lib(TMap<int32, FDZItemPickUpSoundTable>& InMap);
	static void CacheItemDropSoundTable_Lib(TMap<int32, FDZItemDropSoundTable>& InMap);
};
