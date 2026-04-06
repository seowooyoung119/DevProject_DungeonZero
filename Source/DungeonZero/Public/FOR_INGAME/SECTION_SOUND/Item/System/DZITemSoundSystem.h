// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_SOUND/Item/Data/Table/DZItemDropSoundTable.h"
#include "FOR_INGAME/SECTION_SOUND/Item/Data/Table/DZItemPickUpSoundTable.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DZITemSoundSystem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZITemSoundSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	
public:

	static UDZITemSoundSystem* Get(const UObject* InWorldContextObject);

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
	// 드랍 사운드 데이터 가져오기 
	FDZItemPickUpSoundTable* GetItemPickUpSoundTable(const int32 InItemID) { return ItemPickUpSoundDataMap.Find(InItemID);}
	FDZItemDropSoundTable* GetItemDropSoundTable(const int32 InItemID) { return ItemDropSoundDataMap.Find(InItemID);};
	
#pragma endregion
//======================================================================================================================	
#pragma region 시스템_데이터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 시스템_데이터
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	UPROPERTY()
	TMap<int32, FDZItemPickUpSoundTable> ItemPickUpSoundDataMap;
	
	UPROPERTY()
	TMap<int32, FDZItemDropSoundTable> ItemDropSoundDataMap;
	
	// 디버그 
	bool bWantPrintDeBugLog = false;
	
#pragma endregion
//======================================================================================================================	
};
