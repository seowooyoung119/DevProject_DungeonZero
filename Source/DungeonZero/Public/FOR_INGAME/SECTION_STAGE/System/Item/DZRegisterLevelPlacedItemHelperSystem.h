// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZRegisterLevelPlacedItemHelperSystem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZRegisterLevelPlacedItemHelperSystem : public UWorldSubsystem
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
public:
	static UDZRegisterLevelPlacedItemHelperSystem* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================
#pragma region RegisterAPI
	
	//━━━━━━━━━━━━━━━━━━━━
	// RegisterAPI
	//━━━━━━━━━━━━━━━━━━━━
public:
	UFUNCTION(BlueprintCallable, Category = "DZ")
	FORCEINLINE void RegisterLevelPlacedItem(AActor* Actor) { if (!IsValid(GetWorld()) || GetWorld()->GetNetMode() == NM_Client) return; PossibleItems.AddUnique(Actor); };
	
	UFUNCTION(BlueprintCallable, Category = "DZ")
	bool IsThisItemPlaced(AActor* Actor) { return PossibleItems.Contains(Actor); };
	
#pragma endregion
//======================================================================================================================
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> PossibleItems;
	
#pragma endregion	
//======================================================================================================================
		
};
