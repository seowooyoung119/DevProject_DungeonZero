// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/Interface/DZCueVIsualInterface.h"


// Add default functionality here for any IDZCueVIsualInterface functions that are not pure virtual.
bool IDZCueVIsualInterface::GetNiagaraCueData(const FGameplayTag& GATag, TArray<FDZNiagaraCueData>& OutData)
{
	return false;
}

bool IDZCueVIsualInterface::GetDecalCueData(const FGameplayTag& GATag, TArray<FDZDecalCueData>& OutData)
{
	return false;
}

bool IDZCueVIsualInterface::GetMaterialCueData(const FGameplayTag& GATag, TArray<FDZMaterialCueData>& OutData)
{
	return false;
}
