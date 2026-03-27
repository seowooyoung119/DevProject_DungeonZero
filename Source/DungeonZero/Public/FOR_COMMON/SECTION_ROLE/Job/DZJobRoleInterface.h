// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "DZJobRoleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDZJobRoleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZJobRoleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ")
	FGameplayTag GetJobRoleTag() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ")
	void SetJobRole(FGameplayTag& InJobRoleTag);
};
