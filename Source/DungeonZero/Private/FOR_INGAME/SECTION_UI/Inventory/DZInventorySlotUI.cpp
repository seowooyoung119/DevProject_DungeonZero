// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_UI/Inventory/DZInventorySlotUI.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

//=====================================================================================================================
#pragma region 위젯업데이트API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯업데이트API
	//━━━━━━━━━━━━━━━━━━━━

void UDZInventorySlotUI::UpdateSlot(const FDZInventorySlotData& InSlotData)
{
	// 모듈 체크
	if (!IsValid(ItemNameText) || !IsValid(StackSizeText) || !IsValid(ItemIconImage)) return;
	
	// 1. 아이템 존재 여부 확인 (ItemID가 -1이거나 유효하지 않거나 아이템 데이터 스택 갯수가 0이면 빈 슬롯 처리) 
	if (InSlotData.ItemData.StaticDataID == -1 || InSlotData.ItemData.DynamicData.CurrentStack <= 0)
	{
		ItemNameText->SetText(FText::GetEmpty());
		StackSizeText->SetText(FText::GetEmpty());
		ItemIconImage->SetBrushFromTexture(nullptr);
		
		ItemNameText->SetVisibility(ESlateVisibility::Visible);
		StackSizeText->SetVisibility(ESlateVisibility::Visible);
		ItemIconImage->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	// 2. 데이터 테이블에서 상세 정보 가져오기
	UDZItemDataSubSystem* DataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(DataSubSystem)) return;
	FDZITemStaticData* ItemStaticData = DataSubSystem->GetItemStaticData(InSlotData.ItemData.StaticDataID);
	if (!ItemStaticData) return;
	
	// 아이콘 업데이트 
	if (!ItemStaticData->ItemStaticInfo.ItemIcon.IsNull())
	{
		ItemIconImage->SetBrushFromTexture(ItemStaticData->ItemStaticInfo.ItemIcon.LoadSynchronous());
		ItemIconImage->SetVisibility(ESlateVisibility::Visible);
	}

	// 이름 업데이트
	ItemNameText->SetText(ItemStaticData->ItemStaticInfo.ItemName);
	ItemNameText->SetVisibility(ESlateVisibility::Visible);

	// 스캣 업데이트
	StackSizeText->SetText(FText::AsNumber(InSlotData.ItemData.DynamicData.CurrentStack));
	StackSizeText->SetVisibility(ESlateVisibility::Visible);
}

#pragma endregion
//=====================================================================================================================