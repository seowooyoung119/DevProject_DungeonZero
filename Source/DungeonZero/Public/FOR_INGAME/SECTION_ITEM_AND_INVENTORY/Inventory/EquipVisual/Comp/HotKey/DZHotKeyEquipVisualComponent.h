// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/A_Master/DZEquipVisualMasterComponent.h"
#include "DZHotKeyEquipVisualComponent.generated.h"


class ADZItemActorBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZHotKeyEquipVisualComponent : public UDZEquipVisualMasterComponent
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZHotKeyEquipVisualComponent();

#pragma endregion	
//======================================================================================================================	
#pragma region 핫키
	
	//━━━━━━━━━━━━━━━━━━━━
	// 핫키 
	//━━━━━━━━━━━━━━━━━━━━	

public:
	
	// 오너의 스켈레탈 메쉬 특정 부위에 어태치
	void TrySpawnVisual(int32 InTargetHotKeyIndex);
	
	// 든 아이템 디스폰
	void HideSpawnVisual();
	
	// 스왑 
	void SwapSpawnVisual(int32 InTargetHotKeyIndex);
	
protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Hotkey")
	TObjectPtr<ADZItemActorBase> CurrentVisualActor = nullptr;
	
#pragma endregion 
//======================================================================================================================	
	
	
};
