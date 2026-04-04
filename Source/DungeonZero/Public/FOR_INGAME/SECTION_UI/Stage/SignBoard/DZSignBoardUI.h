// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DZSignBoardUI.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZSignBoardUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LevelUiUpdate(int32 Level);
	
};
