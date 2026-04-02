// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventoryInternalHelperLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Library/DZInventorySlotInternalHelperLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemCheckLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"

int32 UDZInventoryInternalHelperLibrary::FindEmptySlot_Lib(const UObject* InWorldContextObject, FDZInventoryCompData& InInventoryCompData, FDZItemRuntimeData& InItemRuntimeData)
{
	// 인벤토리 배열 체크 
	if (InInventoryCompData.InventoryDataArray.IsEmpty()) return -1;
	
	// 인벤토리 데이터 배열 돌면서 체크
	for (int32 Index = 0; Index < InInventoryCompData.InventoryDataArray.Num(); ++Index)
	{
		// 인덱스 유효성 체크
		if (!InInventoryCompData.InventoryDataArray.IsValidIndex(Index)) continue;
		FDZInventorySlotData& SlotData = InInventoryCompData.InventoryDataArray[Index];
		
		// 이미 아이템이 있으면 건너뛰기
		if (UDZInventorySlotInternalHelperLibrary::IsSlotEmpty_Lib(SlotData) == false) continue;
		
		// 슬롯 타입 체크
		if (!UDZInventorySlotInternalHelperLibrary::IsSlotCanAcceptItem_Lib(InWorldContextObject, SlotData, InItemRuntimeData)) continue;
		
		// 비었으면 인덱스 반환
		return Index;
	}
	
	return -1;
}

int32 UDZInventoryInternalHelperLibrary::FindStackSlot_Lib(const UObject* InWorldContextObject, FDZInventoryCompData& InInventoryCompData, FDZItemRuntimeData& InItemRuntimeData)
{
	// 인벤토리 배열 체크 
	if (InInventoryCompData.InventoryDataArray.IsEmpty()) return -1;
	
	// 인벤토리 데이터 배열 돌면서 체크
	for (int32 Index = 0; Index < InInventoryCompData.InventoryDataArray.Num(); ++Index)
	{
		// 인덱스 유효성 체크
		if (!InInventoryCompData.InventoryDataArray.IsValidIndex(Index)) continue;
		FDZInventorySlotData& SlotData = InInventoryCompData.InventoryDataArray[Index];
		
		// 비었으면 건너뛰기 
		if (UDZInventorySlotInternalHelperLibrary::IsSlotEmpty_Lib(SlotData) == true) continue;
		
		// 슬롯 타입 체크
		if (!UDZInventorySlotInternalHelperLibrary::IsSlotCanAcceptItem_Lib(InWorldContextObject, SlotData, InItemRuntimeData)) continue;
		
		// 같은 아이템인지 체크하기
		if (!UTSItemCheckLibrary::IsThisSameItem_Lib(SlotData.ItemData, InItemRuntimeData)) continue;
 		
		// 넣을 수 있는지지 체크하기 
		if (SlotData.ItemData.DynamicData.CurrentStack >= UTSItemCheckLibrary::GetMaxStackSize_Lib(InWorldContextObject, SlotData.ItemData)) continue;
		
		// 같은 아이템이고 최대 스택이 아니면 해당 인덱스 반환
		return Index;
	}
	
	return -1;
}

bool UDZInventoryInternalHelperLibrary::AddItemToEmptySlot_Lib(const UObject* InWorldContextObject, FDZInventorySlotData& InTargetSlot, FDZItemRuntimeData& InItemRuntimeData)
{
 	// 1. 슬롯의 데이터 통째로 복사
	InTargetSlot.ItemData = InItemRuntimeData;
	
	// 2. 들어온 데이터 레퍼런스로 접근해서 정적 데이터와 스택 수 없애기
	InItemRuntimeData.DynamicData.CurrentStack = -1;
	InItemRuntimeData.StaticDataID = -1;
	
	return true;
}

bool UDZInventoryInternalHelperLibrary::AddItemToStackSlot_Lib(const UObject* InWorldContextObject, FDZInventorySlotData& InTargetSlot, FDZItemRuntimeData& InItemRuntimeData)
{
	// 남은 스택 수와 최대 스택 수 
	int32 RemainStack = 0;
	int32 MaxStackSize = UTSItemCheckLibrary::GetMaxStackSize_Lib(InWorldContextObject, InTargetSlot.ItemData);

	// 1. 스택 수 증가 후 
	InTargetSlot.ItemData.DynamicData.CurrentStack += InItemRuntimeData.DynamicData.CurrentStack;

	
	// 2 스택이 넘었는지 체크 -> 남은 스택 값 기억 -> 최대로 클램핑
	if (InTargetSlot.ItemData.DynamicData.CurrentStack >  MaxStackSize)
	{
		RemainStack = InTargetSlot.ItemData.DynamicData.CurrentStack - MaxStackSize;
		InTargetSlot.ItemData.DynamicData.CurrentStack = MaxStackSize;
	}
	
	// 3. 남은 스택이 0 이상이면 그만큼만 들어온 데이터 페런스로 접근해서 깎기
	if (RemainStack > 0)
	{
		InItemRuntimeData.DynamicData.CurrentStack = RemainStack;
	}
	// 3. 남은 스택이 없을 경우 들어온 데이터 레퍼런스로 접근해서 정적 데이터와 스택 수 없애기
	else
	{
		InItemRuntimeData.DynamicData.CurrentStack = 0;
		InItemRuntimeData.StaticDataID = -1;
	}
	
	return true;
}

bool UDZInventoryInternalHelperLibrary::AddItemToMatchSlotType_Lib(const UObject* InWorldContextObject, FDZInventoryCompData& InInventoryCompData, EDZInventorySlotType& InTargetSlotType, FDZItemRuntimeData& InItemRuntimeData)
{
	// 인벤토리 배열 체크 
	if (InInventoryCompData.InventoryDataArray.IsEmpty()) return false;
	
	// 인벤토리 데이터 배열 돌면서 체크
	for (int32 Index = 0; Index < InInventoryCompData.InventoryDataArray.Num(); ++Index)
	{
		// 인덱스 유효성 체크
		if (!InInventoryCompData.InventoryDataArray.IsValidIndex(Index)) continue;
		FDZInventorySlotData& SlotData = InInventoryCompData.InventoryDataArray[Index];

		// 같은 슬롯 타입인지 체크
		if (SlotData.InventorySlotType != InTargetSlotType) continue;
		
		// 비어있지 않으면 건너뛰기  [TODO : 나중에 갈아끼우는 로직을 만들어야할듯]
		if (!UDZInventorySlotInternalHelperLibrary::IsSlotEmpty_Lib(SlotData) == true) continue;
		
		// 넣을 수 있는지 체크하기 
		if (SlotData.ItemData.DynamicData.CurrentStack >= UTSItemCheckLibrary::GetMaxStackSize_Lib(InWorldContextObject, SlotData.ItemData)) continue;
		
		// 아이템 넣기
		// 슬롯의 데이터 통째로 복사
		SlotData.ItemData = InItemRuntimeData;
	
		// 들어온 데이터 레퍼런스로 접근해서 정적 데이터와 스택 수 없애기
		InItemRuntimeData.DynamicData.CurrentStack = -1;
		InItemRuntimeData.StaticDataID = -1;
		
		return true;
	}
	
	return false;
}

FDZInventorySlotData* UDZInventoryInternalHelperLibrary::GetSlotDatabyType_Lib(FDZInventoryCompData& InInventoryCompData, EDZInventorySlotType& InTargetSlotType)
{
	// 인벤토리 배열 체크 
	if (InInventoryCompData.InventoryDataArray.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("장인벤토리 배열 체크 실패"))
		return nullptr;
	}
	// 인벤토리 데이터 배열 돌면서 체크
	for (int32 Index = 0; Index < InInventoryCompData.InventoryDataArray.Num(); ++Index)
	{
		// 인덱스 유효성 체크
		if (!InInventoryCompData.InventoryDataArray.IsValidIndex(Index)) continue;
		FDZInventorySlotData& SlotData = InInventoryCompData.InventoryDataArray[Index];

		UE_LOG(LogTemp, Warning, TEXT("장인벤토리 배열 체크 들어가려는 슬롯의 타입: %s"), *UEnum::GetValueAsString(SlotData.InventorySlotType));
		UE_LOG(LogTemp, Warning, TEXT("장인벤토리 배열 체크 아이템이 들어갈 수 있는 슬롯의 타입: %s"), *UEnum::GetValueAsString(InTargetSlotType));
		
		// 같은 슬롯 타입인지 체크
		if (SlotData.InventorySlotType != InTargetSlotType) continue;
		
		// 반환
		return &SlotData;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("장인벤토리 배열 체크 실패 하나도 못 찾음"))
	return nullptr;
	
}
