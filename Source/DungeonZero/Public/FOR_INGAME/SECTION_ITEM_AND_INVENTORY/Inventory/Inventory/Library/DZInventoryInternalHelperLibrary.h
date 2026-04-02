// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Struct/InventoryCompData/DZInventoryCompData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZInventoryInternalHelperLibrary.generated.h"

/**
 * 인벤토리 내부 사용 전용 라이브러리 
 * :: 인벤토리 클래스에 너무 많은 API가 들어있는 것을 방지하기 위함.
 */
UCLASS()
class DUNGEONZERO_API UDZInventoryInternalHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	// 아무 빈 슬롯 찾기 
	static int32 FindEmptySlot_Lib(const UObject* InWorldContextObject, FDZInventoryCompData& InInventoryCompData, FDZItemRuntimeData& InItemRuntimeData);
	
	// 들어갈 수 있는 스택 슬롯 찾기 
	static int32 FindStackSlot_Lib(const UObject* InWorldContextObject, FDZInventoryCompData& InInventoryCompData, FDZItemRuntimeData& InItemRuntimeData);
	
	// 빈 슬롯에 넣기
	static bool AddItemToEmptySlot_Lib(const UObject* InWorldContextObject, FDZInventorySlotData& InTargetSlot, FDZItemRuntimeData& InItemRuntimeData);
	
	// 스택 슬롯에 넣기 
	static bool AddItemToStackSlot_Lib(const UObject* InWorldContextObject, FDZInventorySlotData& InTargetSlot, FDZItemRuntimeData& InItemRuntimeData);

	// 타입에 맞는 슬롯에 넣기
	static bool AddItemToMatchSlotType_Lib(const UObject* InWorldContextObject, FDZInventoryCompData& InInventoryCompData, EDZInventorySlotType& InTargetSlotType, FDZItemRuntimeData& InItemRuntimeData);
	
	// 타입에 맞는 슬롯 가져오기
	static FDZInventorySlotData* GetSlotDatabyType_Lib(FDZInventoryCompData& InInventoryCompData, EDZInventorySlotType& InTargetSlotType);
	
};
