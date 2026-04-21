// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_STAGE/Data/Struct/DZFakeAnomalySeeInfo.h"
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
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	static UDZChooseBecomeAnomalyActorHelperSystem* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━
protected:
	/**
	 * @param InPossibleActors 후보 액터들
	 * @param MinCount 최소 선택 개수
	 * @param MaxCount 최대 선택 개수
	 * @return 랜덤하게 선택된 액터들의 배열
	 */
	// 진짜 이상현상 선택 API
	TArray<AActor*> ChooseRealAnomalyActors_internal(const TArray<AActor*>& InPossibleActors, int32 MinCount, int32 MaxCount);
	
	// 이전에 선택된 원본 목록 (진짜 전용)
	UPROPERTY()
	TArray<AActor*> PreviousSelectedActors;
	
	/**
	 * @param InPossibleActors 후보 액터들
	 * @param RealAnomaliesSelectedActors 진짜 이상현상으로 바뀌게 선정된 원본들
	 * @param MinCount 최소 선택 개수
	 * @param MaxCount 최대 선택 개수
	 * @return 랜덤하게 선택된 액터들의 구조체 배열
	 */
	// 가짜 이상현상 선택 API
	TArray<FDZFakeAnomalySeeInfo> ChooseFakeAnomalyActors_internal(const TArray<AActor*>& InPossibleActors, TArray<AActor*>& RealAnomaliesSelectedActors, int32 MinCount, int32 MaxCount);
	
#pragma endregion	
//======================================================================================================================		
};
