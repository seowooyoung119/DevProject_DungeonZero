// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemCheckLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"

bool UTSItemCheckLibrary::IsThisItemValid_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData)
{
	// 아이템 데이터 매니저로부터 정적 데이터 포인터 유효한지 체크
	UDZItemDataSubSystem* NewItemDataSubSystem =  UDZItemDataSubSystem::Get(InWorldContextObject);
	if (!IsValid(NewItemDataSubSystem)) return false;
	FDZITemStaticData* FouNewITemStaticData = NewItemDataSubSystem->GetItemStaticData(InItemRuntimeData.StaticDataID);
	if (!FouNewITemStaticData) return false;
	
	// 다이나믹 데이터에 스택 수가 0 이하인지 체크 (넣을 게 없다는 소리)
	if (InItemRuntimeData.DynamicData.CurrentStack <= 0) return false;
	
	// 1 이상이면 넣을 수 있음 
	return true;
}

bool UTSItemCheckLibrary::IsThisITemCanStack_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData)
{
	// 아이템 데이터 매니저로부터 정적 데이터 포인터 유효한지 체크
	UDZItemDataSubSystem* NewItemDataSubSystem =  UDZItemDataSubSystem::Get(InWorldContextObject);
	if (!IsValid(NewItemDataSubSystem)) return false;
	FDZITemStaticData* FouNewITemStaticData = NewItemDataSubSystem->GetItemStaticData(InItemRuntimeData.StaticDataID);
	if (!FouNewITemStaticData) return false;
	
	// 다이나믹 데이터에 스택 수가 0 이상인지 체크
	if (InItemRuntimeData.DynamicData.CurrentStack <= 0) return false;
	
	// 정적데이터에서 아이템이 스택이 가능한지 확인하기 (1보다 작거나 같으면 스택이 불가능하다고 판단)
	if (FouNewITemStaticData->ItemStaticInfo.MaxStackSize <= 1) return false;
	
	// 2 이상이면 스택 가능
	return true;
}

int32 UTSItemCheckLibrary::GetMaxStackSize_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData)
{
	// 아이템 데이터 매니저로부터 정적 데이터 포인터 유효한지 체크
	UDZItemDataSubSystem* NewItemDataSubSystem =  UDZItemDataSubSystem::Get(InWorldContextObject);
	if (!IsValid(NewItemDataSubSystem)) return false;
	FDZITemStaticData* FouNewITemStaticData = NewItemDataSubSystem->GetItemStaticData(InItemRuntimeData.StaticDataID);
	if (!FouNewITemStaticData) return false;
	
	// 최대 스택 사이즈 반환
	return FouNewITemStaticData->ItemStaticInfo.MaxStackSize;
}

bool UTSItemCheckLibrary::IsThisItemCanPlaceInThisInventory_Lib(const UObject* InWorldContextObject, FDZItemRuntimeData& InItemRuntimeData, FDZInventoryCompData& InInventoryData)
{
	// 아이템 데이터 매니저로부터 정적 데이터 포인터 유효한지 체크
	UDZItemDataSubSystem* NewItemDataSubSystem =  UDZItemDataSubSystem::Get(InWorldContextObject);
	if (!IsValid(NewItemDataSubSystem)) return false;
	FDZITemStaticData* FouNewITemStaticData = NewItemDataSubSystem->GetItemStaticData(InItemRuntimeData.StaticDataID);
	if (!FouNewITemStaticData) return false;
	
	// 하나라도 들어갈 수 있는 인벤토리 타입이 있는지 체크 (false 값이면 없다는 뜻이므로 false 반환)
	if (!FouNewITemStaticData->ItemStaticInfo.MatchInventoryCompType.Contains(InInventoryData.InventoryType)) return false;
	
	// 있으면 true 반환
	return true;
}

bool UTSItemCheckLibrary::IsThisSameItem_Lib(FDZItemRuntimeData InFromSlotItemData, FDZItemRuntimeData InItemRuntimeData)
{
	//  같은 ID 인지 체크
	return InFromSlotItemData.StaticDataID == InItemRuntimeData.StaticDataID;
}