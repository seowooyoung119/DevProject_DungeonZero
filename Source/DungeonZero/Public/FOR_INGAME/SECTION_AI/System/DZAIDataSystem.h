// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_AI/Data/Table/DZAIClassTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DZAIDataSystem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAIDataSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 게터
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	
public:

	static UDZAIDataSystem* Get(const UObject* InWorldContextObject);

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부 API
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	// 정적 데이터 가져오기 
	FDZAIClassTable* GetItemStaticData(int32 InItemID);

#pragma endregion
//======================================================================================================================	
#pragma region 내부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 내부 API
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	// 데이터 테이블 캐싱 총괄 함수 
	void InitializeItemStaticData_internal();
	
#pragma endregion
//======================================================================================================================	
#pragma region 시스템_데이터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 시스템_데이터
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	// 데이터 맵 (조회용 캐싱) -> 패키징 문제로 복사 실시
	UPROPERTY()
	TMap<int32, FDZAIClassTable> AIDataMap;
	
	// 디버그 
	bool bWantPrintDeBugLog = false;
	
#pragma endregion
//======================================================================================================================		
};
