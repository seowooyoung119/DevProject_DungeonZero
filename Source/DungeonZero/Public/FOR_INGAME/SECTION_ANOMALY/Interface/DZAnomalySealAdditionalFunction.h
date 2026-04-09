// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DZAnomalySealAdditionalFunction.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDZAnomalySealAdditionalFunction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZAnomalySealAdditionalFunction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	// GAS로 하기 비효율적이거나 액터와 연관이 되어 있을 경우 이 인터페이스의 API를 상속하여 로직을 추가한 뒤 GAS의 EndAbility 에서 인터페이스 호출 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | AnomalySeal")
	void AnomalySealAdditionalFunction();
	
};
