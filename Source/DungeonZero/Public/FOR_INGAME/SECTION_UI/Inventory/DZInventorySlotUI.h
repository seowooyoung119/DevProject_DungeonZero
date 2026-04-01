// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Struct/InventorySlot/DZInventorySlotData.h"
#include "DZInventorySlotUI.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInventorySlotUI : public UUserWidget
{
	GENERATED_BODY()
	
//=====================================================================================================================
#pragma region 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
protected:
	
	 // 아이템 아이콘 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ItemIconImage = nullptr;

	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText= nullptr;

	// 아이템 갯수 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> StackSizeText = nullptr;

#pragma endregion
//=====================================================================================================================
#pragma region 위젯업데이트API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯업데이트API
	//━━━━━━━━━━━━━━━━━━━━
public:
	/** 슬롯 데이터에 맞게 UI 갱신 */
	UFUNCTION(BlueprintCallable, Category = "DZ | Inventory")
	void UpdateSlot(const FDZInventorySlotData& InSlotData);

#pragma endregion
//=====================================================================================================================
};
