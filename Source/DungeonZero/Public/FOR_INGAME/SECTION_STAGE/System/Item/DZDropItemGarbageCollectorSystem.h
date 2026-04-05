// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZDropItemGarbageCollectorSystem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZDropItemGarbageCollectorSystem : public UWorldSubsystem
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
public:
	static UDZDropItemGarbageCollectorSystem* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================
#pragma region 드랍아이템가비지컬렉터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 드랍아이템가비지컬렉터
	//━━━━━━━━━━━━━━━━━━━━
public:
	UFUNCTION(BlueprintCallable, Category = "DZ")
	FORCEINLINE void RegisterDropItem(AActor* Actor) { if (!IsValid(GetWorld()) || GetWorld()->GetNetMode() == NM_Client) return; DropItems.AddUnique(Actor); }

	UFUNCTION(BlueprintCallable, Category = "DZ")
	void UnRegisterThisItem(AActor* Actor) { DropItems.Remove(Actor);}
	
	UFUNCTION(BlueprintCallable, Category = "DZ")
	void GCAllDropItems();
	
#pragma endregion
//======================================================================================================================
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> DropItems;
	
#pragma endregion	
//======================================================================================================================
			
};
