// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_UI/Interact/Item/DZItemInteractToggleUI.h"
#include "Components/TextBlock.h"

//======================================================================================================================	
#pragma region ItemUIAPI		

	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
void UDZItemInteractToggleUI::InitInteractInfo(const FText& Text, const FText& InteractKeyText)
{
	if (!IsValid(ItemNameTextBlock)) return;
	if (!IsValid(InteractKeyTextBlock)) return;
	
	ItemNameTextBlock->SetText(Text);
	InteractKeyTextBlock->SetText(InteractKeyText);
}

#pragma endregion	
//======================================================================================================================