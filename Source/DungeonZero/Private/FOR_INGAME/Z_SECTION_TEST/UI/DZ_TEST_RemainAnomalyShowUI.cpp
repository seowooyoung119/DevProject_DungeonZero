// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/Z_SECTION_TEST/UI/DZ_TEST_RemainAnomalyShowUI.h"
#include "Components/TextBlock.h"

void UDZ_TEST_RemainAnomalyShowUI::UpdateRemainAnomaly(const int32 InRemainAnomaly)
{
	if (!IsValid(RemainAnomalyTextBlock)) return;
	FText Text = FText::AsNumber(InRemainAnomaly);
	RemainAnomalyTextBlock->SetText(Text);
}
