// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZChooseBecomeAnomalyActorHelperSystem.generated.h"

/**
 * 역할 : 스테이지에서 어노말리가 될 수 있는 액터 중 랜덤으로 선택.
 */
UCLASS()
class DUNGEONZERO_API UDZChooseBecomeAnomalyActorHelperSystem : public UWorldSubsystem
{
	friend class UDZStageControlSystem;
	
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region Getter
public:
	static UDZChooseBecomeAnomalyActorHelperSystem* Get(const UObject* WorldContextObject);
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI
protected:
	/**
	 * @param InPossibleActors 후보 액터들
	 * @param MinCount 최소 선택 개수
	 * @param MaxCount 최대 선택 개수
	 * @return 랜덤하게 선택된 액터들의 배열
	 */
	UFUNCTION(BlueprintCallable, Category = "DZ|Stage")
	TArray<AActor*> ChooseRandomAnomalyActors_internal(const TArray<AActor*>& InPossibleActors, int32 MinCount, int32 MaxCount);
	
#pragma endregion	
//======================================================================================================================		
};
