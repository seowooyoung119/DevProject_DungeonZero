// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Item/DZRegisterLevelPlacedItemHelperSystem.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

UDZRegisterLevelPlacedItemHelperSystem* UDZRegisterLevelPlacedItemHelperSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZRegisterLevelPlacedItemHelperSystem* RegisterLevelPlacedItemHelperSystem = World->GetSubsystem<UDZRegisterLevelPlacedItemHelperSystem>();
	if (!IsValid(RegisterLevelPlacedItemHelperSystem)) return nullptr;
	
	return RegisterLevelPlacedItemHelperSystem;
	
}

#pragma endregion
//======================================================================================================================