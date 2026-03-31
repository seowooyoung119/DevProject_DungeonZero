// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventorySlotInternalHelperLibrary.h"

bool UDZInventorySlotInternalHelperLibrary::IsSlotEmpty_Lib(FDZInventorySlotData& InInventorySlotData)
{
	// 동적 데이터 스택 체크
	bool bIsCurrentStackEmpty = (InInventorySlotData.ItemData.DynamicData.CurrentStack <= 0);
	
	// 정적 데이터 ID 체크 
	bool bIsStaticDataIDEmpty = (InInventorySlotData.ItemData.StaticDataID <= 0);
	
	// 모든 체크가 확인 되면 true
	return (bIsCurrentStackEmpty && bIsStaticDataIDEmpty);
}

bool UDZInventorySlotInternalHelperLibrary::ReduceItemFromSlot_Lib(FDZInventorySlotData& InInventorySlotData, int32 DeleteCount)
{
	// 갯수만큼 차감
	InInventorySlotData.ItemData.DynamicData.CurrentStack -= DeleteCount;

	// 만약에 0이다? -> 초기화
	if (InInventorySlotData.ItemData.DynamicData.CurrentStack <= 0)
	{
		RemoveItemFromSlot_Lib(InInventorySlotData);
	}
	
	return true;
}

bool UDZInventorySlotInternalHelperLibrary::RemoveItemFromSlot_Lib(FDZInventorySlotData& InInventorySlotData)
{
	// 정적 데이터 초기화
	InInventorySlotData.ItemData.StaticDataID = -1;
	
	// 동적 데이터 초기화 
	InInventorySlotData.ItemData.DynamicData.CurrentStack = 0;
	
	return true;
}