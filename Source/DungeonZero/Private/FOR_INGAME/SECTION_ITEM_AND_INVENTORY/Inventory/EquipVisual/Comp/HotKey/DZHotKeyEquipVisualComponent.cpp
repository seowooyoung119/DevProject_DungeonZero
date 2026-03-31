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
	UDZHotKeyInventoryComponent* HotKeyInventoryComponent =	IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryCompo(GetOwner());
	if (!IsValid(HotKeyInventoryComponent)) return;
	
	// 2. 슬롯 유효 체크
	FDZInventoryCompData& InventoryCompData = HotKeyInventoryComponent->GetInventoryData();
	if (!InventoryCompData.InventoryDataArray.IsValidIndex(InTargetHotKeyIndex)) return;
	
	// 3. 정적 데이터 체크
	UDZItemDataSubSystem* ItemDataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(ItemDataSubSystem)) return;
	FDZITemStaticData* ItemStaticData = ItemDataSubSystem->GetItemStaticData(InventoryCompData.InventoryDataArray[InTargetHotKeyIndex].ItemData.StaticDataID);
	if (ItemStaticData == nullptr) return;
	
	if (!ItemDataSubSystem->ItemStaticDataMap_ItemClass.Contains(ItemStaticData->ItemStaticInfo.ItemID)) return;

	TSubclassOf<AActor>* FoundClassPtr = ItemDataSubSystem->ItemStaticDataMap_ItemClass.Find(ItemStaticData->ItemStaticInfo.ItemID);
	if (FoundClassPtr == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Map에 해당 ID가 없음"));
		return;
	}
	
	UClass* ActualClass = FoundClassPtr->Get(); 
	if (!ActualClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : TSubclassOf 내부 클래스가 None임"));
		return;
	}
	
	// 6. 스폰 옵션 및 오너 설정 
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();

	// 7. 스폰 실시 
	AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(ActualClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	if (!IsValid(SpawnActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Spawn Failed"));
		return;
	}
	
	ADZItemActorBase* CaseItem = Cast<ADZItemActorBase>(SpawnActor);
	if (!IsValid(CaseItem))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : CaseItem Invalid"));
		if (IsValid(CurrentVisualActor)) CurrentVisualActor->Destroy();
		return;
	}
	
	CurrentVisualActor = CaseItem;
	
	// 8. 피직스, 콜리전 끄기 
	CurrentVisualActor->SetTogglePhysicsAndCollisions(false);
	
	// 9. 오너의 메쉬 소켓에 붙이기 (예: "Hand_R_Socket")
	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!IsValid(OwnerChar))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : OwnerChar Invalid"));
		CurrentVisualActor->Destroy();
		return;
	}
	if (!IsValid(OwnerChar->GetMesh()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Mesh Invalid"));
		CurrentVisualActor->Destroy();
		return;
	}
	bool IsAttachSuccess = CurrentVisualActor->AttachToComponent(OwnerChar->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, ItemStaticData->ItemStaticInfo.HotKeyAttachSocketName);
	if (!IsAttachSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("TrySpawnVisual : Attach Failed"));
		CurrentVisualActor->Destroy();
		return;
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