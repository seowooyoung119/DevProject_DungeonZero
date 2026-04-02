// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/A_Master/DZInventoryMasterComponent.h"
#include "DZBodyEquipInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZBodyEquipInventoryComponent : public UDZInventoryMasterComponent
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZBodyEquipInventoryComponent();

#pragma endregion
//======================================================================================================================	
};
