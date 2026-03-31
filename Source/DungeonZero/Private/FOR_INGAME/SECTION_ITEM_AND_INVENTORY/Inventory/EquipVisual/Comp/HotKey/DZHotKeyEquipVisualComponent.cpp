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
	// 1. 핫키 인벤토리 컴포넌트 가져오기
	if (!IsValid(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : GetOwner() is not valid"));
		return;
	}
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryCompo(GetOwner());
	if (!IsValid(HotKeyInventoryComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : HotKeyInventoryComponent is not valid"));
		return;
	}
	
	// 슬롯 유효 체크
	FDZInventoryCompData& InventoryCompData = HotKeyInventoryComponent->GetInventoryData();
	if (!InventoryCompData.InventoryDataArray.IsValidIndex(InTargetHotKeyIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : InTargetHotKeyIndex is not valid"));
		return;
	}
	
	// 정적 데이터 체크
	UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(ItemDataSubSystem))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : ItemDataSubSystem is not valid"));
		return;
	}
	FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(InventoryCompData.InventoryDataArray[InTargetHotKeyIndex].ItemData.StaticDataID);
	if (!ItemStaticData)
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : ItemStaticData is not valid"));
		return;
	}
	// 소환 아이템 체크 
	if (!IsValid(ItemStaticData->ItemStaticInfo.ItemClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : ItemStaticData->ItemStaticInfo.ItemClass is not valid"));
		return;
	}
	// 3. 스폰 옵션 및 오너 설정 
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();

	// 스폰 실시 
	CurrentVisualActor = GetWorld()->SpawnActor<ADZItemActorBase>(ItemStaticData->ItemStaticInfo.ItemClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!IsValid(CurrentVisualActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : CurrentVisualActor is not valid"));
		return;
	}
	
	// 피직스, 콜리전 끄기 
	CurrentVisualActor->SetTogglePhysicsAndCollisions(false);
	
	// 오너의 메쉬 소켓에 붙이기 (예: "Hand_R_Socket")
	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!IsValid(OwnerChar))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : OwnerChar is not valid"));
		CurrentVisualActor->Destroy();
		return;
	}
	
	if (!IsValid(OwnerChar->GetMesh()))
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : OwnerChar->GetMesh() is not valid"));
		CurrentVisualActor->Destroy();
		return;
	}
	
	bool IsAttachSuccess = CurrentVisualActor->AttachToComponent(OwnerChar->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, ItemStaticData->ItemStaticInfo.HotKeyAttachSocketName);
	if (!IsAttachSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : AttachToComponent is not valid"));
		CurrentVisualActor->Destroy();
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : AttachToComponent is valid"));
	}
}

void UDZHotKeyEquipVisualComponent::HideSpawnVisual()
{
	if (!IsValid(CurrentVisualActor)) return;
	CurrentVisualActor->Destroy();
	CurrentVisualActor = nullptr;
}

void UDZHotKeyEquipVisualComponent::SwapSpawnVisual(int32 InTargetHotKeyIndex)
{
	// 기존꺼 일단 지우고
	HideSpawnVisual();
    
	// 새 인덱스로 다시 생성
	TrySpawnVisual(InTargetHotKeyIndex);
}

#pragma endregion
//======================================================================================================================	