// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZRegisterAllCanBeAnomalyActorHelperSystem.generated.h"

/**
 * 역할 : 스테이지에 어노말리 가능한 모든 액터를 수집하는 시스템 
 */
UCLASS()
class DUNGEONZERO_API UDZRegisterAllCanBeAnomalyActorHelperSystem : public UWorldSubsystem
{
	
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
public:
	static UDZRegisterAllCanBeAnomalyActorHelperSystem* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================
#pragma region RegisterAPI
	
	//━━━━━━━━━━━━━━━━━━━━
	// RegisterAPI
	//━━━━━━━━━━━━━━━━━━━━
public:
	UFUNCTION(BlueprintCallable, Category = "DZ")
	FORCEINLINE void RegisterAllCanBeAnomalyActor(AActor* Actor) { if (!IsValid(GetWorld()) || GetWorld()->GetNetMode() == NM_Client) return; PossibleActors.AddUnique(Actor); };
	
#pragma endregion
//======================================================================================================================
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	TArray<AActor*>& GetPossibleActors() { return PossibleActors; };
	
protected:
	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "DZ")
	TArray<AActor*> PossibleActors;
	
#pragma endregion	
//======================================================================================================================
	
};
