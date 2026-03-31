// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemSpawnSubSystem.h"

#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	

UDZItemSpawnSubSystem* UDZItemSpawnSubSystem::Get(const UObject* InWorldContextObject)
{
	if (!IsValid(InWorldContextObject)) return nullptr;
	
	UWorld* World = InWorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
			
	UGameInstance* GameInstance = World->GetGameInstance();

	UDZItemSpawnSubSystem* ItemSpawnSubSystem = GameInstance->GetSubsystem<UDZItemSpawnSubSystem>();
	if (!IsValid(ItemSpawnSubSystem)) return nullptr;

	return ItemSpawnSubSystem;
}

#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부 API
	//━━━━━━━━━━━━━━━━━━━━
ADZItemActorBase* UDZItemSpawnSubSystem::SpawnNewItem(int32 InSpawnItemID, int32 InWantStackSize, FVector& InSpawnLocation, FRotator& InSpawnRotation)
{
	// 정적 데이터 가져오기
	UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(this);
	if (!IsValid(ItemDataSubSystem)) return nullptr;
	FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(InSpawnItemID);
	if (!ItemStaticData) return nullptr;
	
	// 월드 및 스폰할 액터 클래스 데이터 체크 
	if (!IsValid(GetWorld())) return nullptr;
	if (!IsValid(ItemStaticData->ItemStaticInfo.ItemClass)) return nullptr;
	
	// 스폰 실시 
	ADZItemActorBase* SpawnedItemActor = GetWorld()->SpawnActor<ADZItemActorBase>(ItemStaticData->ItemStaticInfo.ItemClass, InSpawnLocation, InSpawnRotation);
	if (!IsValid(SpawnedItemActor)) return nullptr;
	
	// 새 아이템 데이터 생성 
	FDZItemRuntimeData NewItemRuntimeData;
	NewItemRuntimeData.DynamicData.CurrentStack = InWantStackSize;
	NewItemRuntimeData.StaticDataID = InSpawnItemID;
	
	// 새 데이터 주입
	SpawnedItemActor->SetItemRuntimeData(NewItemRuntimeData);
	return SpawnedItemActor;
}

ADZItemActorBase* UDZItemSpawnSubSystem::DropItemFromSomeWhere(FDZItemRuntimeData& InItemRuntimeData, FVector& InDropLocation, FRotator& InDropRotation)
{
	// 정적 데이터 가져오기
	UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(this);
	if (!IsValid(ItemDataSubSystem)) return nullptr;
	FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(InItemRuntimeData.StaticDataID);
	if (!ItemStaticData) return nullptr;
	
	// 월드 및 스폰할 액터 클래스 데이터 체크 
	if (!IsValid(GetWorld())) return nullptr;
	if (!IsValid(ItemStaticData->ItemStaticInfo.ItemClass)) return nullptr;
	
	// 스폰 실시 
	ADZItemActorBase* SpawnedItemActor = GetWorld()->SpawnActor<ADZItemActorBase>(ItemStaticData->ItemStaticInfo.ItemClass, InDropLocation, InDropRotation);
	if (!IsValid(SpawnedItemActor)) return nullptr;
	
	// 기존 데이터 주입 
	SpawnedItemActor->SetItemRuntimeData(InItemRuntimeData);
	return SpawnedItemActor;
}

#pragma endregion
//======================================================================================================================	