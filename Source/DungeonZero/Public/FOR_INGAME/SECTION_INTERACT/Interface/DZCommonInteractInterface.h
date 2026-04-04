// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DZCommonInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDZCommonInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZCommonInteractInterface
{
	GENERATED_BODY()

public:
	// 토글 위젯 켜기 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Interact")
	void ToggleInteractWidget(bool InWantOn);
	
	// 문, 레버 같은 어떤 액터가 하는 로직 (반환값이 필요 없는 기능을 의미)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Interact")
	void DoStandAloneInteractLogic();
	
};
