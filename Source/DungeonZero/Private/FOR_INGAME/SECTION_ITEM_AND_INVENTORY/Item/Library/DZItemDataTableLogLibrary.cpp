// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Library/DZItemDataTableLogLibrary.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"

void UTSItemDataTableLogLibrary::LogStaticItemData_Lib(FDZITemStaticData* InITemStaticData)
{
	if (!InITemStaticData) return;
	
    const FDZItemInfoTable& Info = InITemStaticData->ItemStaticInfo;

    UE_LOG(LogTemp, Log, TEXT("=================================================="));
    UE_LOG(LogTemp, Log, TEXT("[Item Static Data Log]"));
    
    // 1. 기본 정보 (ID, Name)
    UE_LOG(LogTemp, Log, TEXT("Item ID: %d"), Info.ItemID);
    UE_LOG(LogTemp, Log, TEXT("Item Name: %s"), *Info.ItemName.ToString());
    UE_LOG(LogTemp, Log, TEXT("Item Description: %s"), *Info.ItemDescription.ToString());
    UE_LOG(LogTemp, Log, TEXT("Interact Key: %s"), *Info.ItemInteractKeyType.ToString());

    // 2. 클래스 정보 (TSubclassOf)
    FString ClassName = Info.ItemClass ? Info.ItemClass->GetName() : TEXT("Null");
    UE_LOG(LogTemp, Log, TEXT("Item Class: %s"), *ClassName);

    // 3. 아이콘 경로 (TSoftObjectPtr)
    FString IconPath = Info.ItemIcon.ToSoftObjectPath().ToString();
    UE_LOG(LogTemp, Log, TEXT("Item Icon Path: %s"), *IconPath);

    // 4. 인벤토리 컴포넌트 타입 배열 (Enum Array)
    UE_LOG(LogTemp, Log, TEXT("--- Match Inventory Comp Types (%d) ---"), Info.MatchInventoryCompType.Num());
    for (const EDZInventoryCompType& CompType : Info.MatchInventoryCompType)
    {
        // UEnum을 사용하여 열거형의 이름을 문자열로 변환
        const FString EnumValue = UEnum::GetValueAsString(CompType);
        UE_LOG(LogTemp, Log, TEXT(" - %s"), *EnumValue);
    }

    // 5. 슬롯 타입 배열 (Enum Array)
    UE_LOG(LogTemp, Log, TEXT("--- Match Inventory Slot Types (%d) ---"), Info.MatchInventorySlotType.Num());
    for (const EDZInventorySlotType& SlotType : Info.MatchInventorySlotType)
    {
        const FString EnumValue = UEnum::GetValueAsString(SlotType);
        UE_LOG(LogTemp, Log, TEXT(" - %s"), *EnumValue);
    }

    // 6. 스택 정보
    UE_LOG(LogTemp, Log, TEXT("Max Stack Size: %d"), Info.MaxStackSize);
    UE_LOG(LogTemp, Log, TEXT("=================================================="));
	
}
