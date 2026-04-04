// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Data/Enum/Enum_DZPlayRole.h"
#include "DZCommonPlayRoleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDZCommonPlayRoleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZCommonPlayRoleInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Common | PlayRole")
	EDZPlayRole GetPlayRole();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DZ | Common | PlayRole")
	void ToggleHiddenInGame(bool InIsVisible, bool InbCanCollisionAble);
};
