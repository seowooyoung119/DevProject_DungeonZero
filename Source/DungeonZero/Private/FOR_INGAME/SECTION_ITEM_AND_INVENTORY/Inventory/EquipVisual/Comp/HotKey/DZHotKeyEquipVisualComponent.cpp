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
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority()) return;
	
	// 1. 핫키 인벤토리 컴포넌트 가져오기
	if (!IsValid(GetOwner()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Owner Invalid"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : GetOwner() is not valid"));
		return;
	}
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryCompo(GetOwner());
	if (!IsValid(HotKeyInventoryComponent))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : InventoryComp Invalid"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : HotKeyInventoryComponent is not valid"));
		return;
	}
	
	// 2. 슬롯 유효 체크
	FDZInventoryCompData& InventoryCompData = HotKeyInventoryComponent->GetInventoryData();
	if (!InventoryCompData.InventoryDataArray.IsValidIndex(InTargetHotKeyIndex))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Index Out of Bounds"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : InTargetHotKeyIndex is not valid"));
		return;
	}
	
	// 3. 정적 데이터 체크
	UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(ItemDataSubSystem))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : SubSystem Invalid"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : ItemDataSubSystem is not valid"));
		return;
	}
	FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(InventoryCompData.InventoryDataArray[InTargetHotKeyIndex].ItemData.StaticDataID);
	if (ItemStaticData == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : StaticData Null"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : ItemStaticData is not valid"));
		return;
	}
	
	if (!ItemStaticData->ItemStaticInfo.ItemClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : LoadedClassPtr is Invalid!"));
		return;
	}

	// 6. 스폰 옵션 및 오너 설정 
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();

	// 7. 스폰 실시 
	CurrentVisualActor = GetWorld()->SpawnActor<ADZItemActorBase>(ItemStaticData->ItemStaticInfo.ItemClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (!IsValid(CurrentVisualActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Spawn Failed"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : CurrentVisualActor is not valid"));
		return;
	}
	
	// 8. 피직스, 콜리전 끄기 
	CurrentVisualActor->SetTogglePhysicsAndCollisions(false);
	
	// 9. 오너의 메쉬 소켓에 붙이기 (예: "Hand_R_Socket")
	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!IsValid(OwnerChar))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : OwnerChar Invalid"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : OwnerChar is not valid"));
		CurrentVisualActor->Destroy();
		return;
	}
	if (!IsValid(OwnerChar->GetMesh()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Mesh Invalid"));
		UE_LOG(LogTemp, Warning, TEXT("TrySpawnVisual : OwnerChar->GetMesh() is not valid"));
		CurrentVisualActor->Destroy();
		return;
	}
	bool IsAttachSuccess = CurrentVisualActor->AttachToComponent(OwnerChar->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, ItemStaticData->ItemStaticInfo.HotKeyAttachSocketName);
	if (!IsAttachSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("TrySpawnVisual : Attach Failed"));
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
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority()) return;
	
	if (!IsValid(CurrentVisualActor)) return;
	CurrentVisualActor->Destroy();
	CurrentVisualActor = nullptr;
}

void UDZHotKeyEquipVisualComponent::SwapSpawnVisual(int32 InTargetHotKeyIndex)
{
	// 서버에서만 실시
	if (!IsValid(GetOwner()) || !GetOwner()->HasAuthority()) return;
	
	// 기존꺼 일단 지우고
	HideSpawnVisual();
    
	// 새 인덱스로 다시 생성
	TrySpawnVisual(InTargetHotKeyIndex);
}

#pragma endregion
//======================================================================================================================	