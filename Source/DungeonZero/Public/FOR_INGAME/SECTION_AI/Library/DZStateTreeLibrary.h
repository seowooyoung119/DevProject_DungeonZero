// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZStateTreeLibrary.generated.h"

class AAIController;
class UStateTreeAIComponent;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZStateTreeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "DZ | StateTree")
	static UStateTreeAIComponent* GetStateTreeAIComponentFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category = "DZ | StateTree")
	static UStateTreeAIComponent* GetStateTreeComponentFromController(AController* InController);
	
};
