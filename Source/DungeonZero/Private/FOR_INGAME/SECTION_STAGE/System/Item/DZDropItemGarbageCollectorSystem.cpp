// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Item/DZDropItemGarbageCollectorSystem.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

UDZDropItemGarbageCollectorSystem* UDZDropItemGarbageCollectorSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZDropItemGarbageCollectorSystem* DropItemGarbageCollectorSystem = World->GetSubsystem<UDZDropItemGarbageCollectorSystem>();
	if (!IsValid(DropItemGarbageCollectorSystem)) return nullptr;
	
	return DropItemGarbageCollectorSystem;
}

	
#pragma endregion
//======================================================================================================================
#pragma region 드랍아이템가비지컬렉터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 드랍아이템가비지컬렉터
	//━━━━━━━━━━━━━━━━━━━━

void UDZDropItemGarbageCollectorSystem::GCAllDropItems()
{
	for (AActor* Actor : DropItems)
	{
		if (IsValid(Actor)) Actor->Destroy();
	}
	
	DropItems.Empty();
}

#pragma endregion
//======================================================================================================================