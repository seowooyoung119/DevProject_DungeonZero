// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/A_Master/DZEquipVisualMasterComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Enum/InventorySlotType/DZInventorySlotType.h"
#include "DZBodyEquipVisualComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZBodyEquipVisualComponent : public UDZEquipVisualMasterComponent
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZBodyEquipVisualComponent();
	
#pragma endregion
//======================================================================================================================		
#pragma region 장비
	
	//━━━━━━━━━━━━━━━━━━━━
	// 핫키 
	//━━━━━━━━━━━━━━━━━━━━		
	
public:
	void HandleVisual(TArray<EDZInventorySlotType>& InTargetSlotTypes);
	
protected:
	
	// 스왑 
	void SwapSpawnVisual_internal(EDZInventorySlotType& InTargetSlotType);
	
	// 오너의 스켈레탈 메쉬 특정 부위에 어태치
	void TrySpawnVisual_internal(EDZInventorySlotType& InTargetSlotType);
	
	// 든 아이템 디스폰
	void HideSpawnVisual_internal(EDZInventorySlotType& InTargetSlotType);
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | BodyEquip")
	TMap<EDZInventorySlotType, TObjectPtr<ADZItemActorBase>> AttachedItems;
	
#pragma endregion	
//======================================================================================================================		
	
};
