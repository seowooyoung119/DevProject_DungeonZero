// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DZInGameOverlay.generated.h"

class UBorder;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInGameOverlay : public UUserWidget
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 위젯_모듈
	
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> FadeInoutOBorder = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
