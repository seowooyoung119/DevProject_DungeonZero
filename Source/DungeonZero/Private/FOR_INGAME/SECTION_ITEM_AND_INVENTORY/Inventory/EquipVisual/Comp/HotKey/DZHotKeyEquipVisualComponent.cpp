// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/HotKey/DZHotKeyEquipVisualComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"
#include "GameFramework/Character.h"


//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━

UDZHotKeyEquipVisualComponent::UDZHotKeyEquipVisualComponent()
{
	// tick
	PrimaryComponentTick.bCanEverTick = false;
	
	// network
	SetIsReplicatedByDefault(true);
}

#pragma endregion	
//======================================================================================================================	
#pragma region 핫키
	
	//━━━━━━━━━━━━━━━━━━━━
	// 핫키 
	//━━━━━━━━━━━━━━━━━━━━	

void UDZHotKeyEquipVisualComponent::TrySpawnVisual(int32 InTargetHotKeyIndex)
{
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("서버 아님"));
		return;
	}
	
	// 1. 핫키 인벤토리 컴포넌트 가져오기
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryComponent(GetOwner());
	if (!IsValid(HotKeyInventoryComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("핫키 가져오기 실패"));
		return;
	}
	
	// 2. 슬롯 유효 체크
	FDZInventoryCompData& InventoryCompData = HotKeyInventoryComponent->GetInventoryData();
	if (!InventoryCompData.InventoryDataArray.IsValidIndex(InTargetHotKeyIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("핫키 슬롯 유효 체크 실패"));
		return;
	}
	
	// 3. 정적 데이터 체크
	UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(ItemDataSubSystem))
	{
		UE_LOG(LogTemp, Warning, TEXT("정적 데이터 시스템 체크 실패"));
		return;
	}
	FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(InventoryCompData.InventoryDataArray[InTargetHotKeyIndex].ItemData.StaticDataID);
	if (ItemStaticData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("정적 데이터 가져오기 실패 "));
		return;
	}
	
	CurrentVisualActor = SpawnLogic(*ItemStaticData);
	if (!IsValid(CurrentVisualActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual: CurrentVisualActor == nullptr"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual: CurrentVisualActor 성공"));
	}
}

void UDZHotKeyEquipVisualComponent::HideSpawnVisual()
{
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("HideSpawnVisual: 핫키 가져오기 실패"));
		return;
	}
	
	if (!IsValid(CurrentVisualActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("HideSpawnVisual: 유효하지 않음"));
		return;
	}
	
	CurrentVisualActor->Destroy();
	CurrentVisualActor = nullptr;
}

void UDZHotKeyEquipVisualComponent::SwapSpawnVisual(int32 InTargetHotKeyIndex)
{
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("HideSpawnVisual: 핫키 가져오기 실패"));
		return;
	}
	
	// 기존꺼 일단 지우고
	HideSpawnVisual();
    
	// 새 인덱스로 다시 생성
	TrySpawnVisual(InTargetHotKeyIndex);
}

#pragma endregion
//======================================================================================================================	