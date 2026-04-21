// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Data/Table/DZAnomalySettingTable.h"
#include "FOR_INGAME/SECTION_STAGE/Data/Struct/DZFakeAnomalySeeInfo.h"
#include "Subsystems/WorldSubsystem.h"
#include "DZChangeToAnomalyActorHelperSystem.generated.h"

/**
 * 역할 : 어노말리로 변할 수 있는 선정된 액터를 실제로 어노말리 액터로 변환 
 */
UCLASS()
class DUNGEONZERO_API UDZChangeToAnomalyActorHelperSystem : public UWorldSubsystem
{
	
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	static UDZChangeToAnomalyActorHelperSystem* Get(const UObject* WorldContextObject);
	
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━
	
	/**
	 * @param SelectedActors 이전에 선택된 원본 액터들 for 진짜 (자동으로 숨김)
	 * @return 생성된 진짜 어노말리 액터들의 배열
	 */
	TArray<AActor*> ReplaceWithRealAnomalyActors_internal(const TArray<AActor*>& SelectedActors);
	
	/**
    	 * @param FakeSelectedActors 이전에 선택된 원본 액터들 for 가짜 (자동으로 숨김)
    	 * @return 생성된 가짜 어노말리 액터들의 배열
    	 */
	TArray<AActor*> ReplaceWithFakeAnomalyActors_internal(const TArray<FDZFakeAnomalySeeInfo>& FakeSelectedActors);

#pragma endregion	
//======================================================================================================================
};
