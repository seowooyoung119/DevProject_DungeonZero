// All CopyRight From YulRyongGameStudio //



#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"

#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZHotKeyInventoryComponent::UDZHotKeyInventoryComponent()
{
	// tick
	PrimaryComponentTick.bCanEverTick = false;
	
	// network
	SetIsReplicatedByDefault(true);
}

#pragma endregion
//======================================================================================================================	
