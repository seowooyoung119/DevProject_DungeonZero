// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZITemStaticData.h"
#include "DZItemInteractToggleUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZItemInteractToggleUI : public UUserWidget
{
	GENERATED_BODY()
	
//=====================================================================================================================
#pragma region 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━

protected:
	
	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameTextBlock = nullptr;

	// 아이템 상호작용 키
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractKeyTextBlock = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region ItemUIAPI		

	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
		
public:
	// 초기에 아이템 인터렉트 토글 UI 표시 값 설정하는 함수 
	void InitInteractInfo(const FText& Text, const FText& InteractKeyText);
	
#pragma endregion	
//======================================================================================================================		
};
