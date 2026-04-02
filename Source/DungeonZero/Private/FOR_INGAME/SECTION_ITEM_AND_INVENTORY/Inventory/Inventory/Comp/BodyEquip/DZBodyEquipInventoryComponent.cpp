// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/BodyEquip/DZBodyEquipInventoryComponent.h"


//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZBodyEquipInventoryComponent::UDZBodyEquipInventoryComponent()
{
	// tick
	PrimaryComponentTick.bCanEverTick = false;
	
	// network
	SetIsReplicatedByDefault(true);
}

#pragma endregion
//======================================================================================================================	
