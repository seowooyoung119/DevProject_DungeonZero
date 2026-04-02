// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/A_Master/DZEquipVisualMasterComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZITemStaticData.h"
#include "GameFramework/Character.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZEquipVisualMasterComponent::UDZEquipVisualMasterComponent()
{
	// tick
	PrimaryComponentTick.bCanEverTick = false;
	
	// network
	SetIsReplicatedByDefault(true);
}

ADZItemActorBase* UDZEquipVisualMasterComponent::SpawnLogic(FDZITemStaticData& InItemStaticData)
{
	// 데이터 유효성 체크
	TSubclassOf<AActor> FoundClassPtr = InItemStaticData.ItemStaticInfo.ItemClass;
	if (FoundClassPtr == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Map에 해당 ID가 없음"));
		return nullptr;
	}
	UClass* ActualClass = FoundClassPtr.Get(); 
	if (!ActualClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : TSubclassOf 내부 클래스가 None임"));
		return nullptr;
	}
	
	// 스폰 옵션 및 오너 설정 
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();

	// 스폰 실시 
	AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(ActualClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	if (!IsValid(SpawnActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Spawn Failed"));
		return nullptr;
	}
	
	// 스폰 후 체크
	ADZItemActorBase* CaseItem = Cast<ADZItemActorBase>(SpawnActor);
	if (!IsValid(CaseItem))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : CaseItem Invalid"));
		if (IsValid(SpawnActor)) SpawnActor->Destroy();
		return nullptr;
	}
	
	// 피직스, 콜리전 끄기 
	CaseItem->SetTogglePhysicsAndCollisions(false);
	
	// 오너의 메쉬 소켓에 붙이기 (예: "Hand_R_Socket")
	ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
	if (!IsValid(OwnerChar))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : OwnerChar Invalid"));
		CaseItem->Destroy();
		return nullptr;
	}
	if (!IsValid(OwnerChar->GetMesh()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TrySpawnVisual : Mesh Invalid"));
		CaseItem->Destroy();
		return nullptr;
	}
	bool IsAttachSuccess = CaseItem->AttachToComponent(OwnerChar->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, InItemStaticData.ItemStaticInfo.HotKeyAttachSocketName);
	if (!IsAttachSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("TrySpawnVisual : Attach Failed"));
		CaseItem->Destroy();
		return nullptr;
	}
	
	return CaseItem;
}

#pragma endregion	
//======================================================================================================================		
