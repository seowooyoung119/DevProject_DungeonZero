// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/Item/System/DZITemSoundSystem.h"
#include "FOR_INGAME/SECTION_SOUND/Item/Library/DZItemSoundSystemCachingHelperLibrary.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	

UDZITemSoundSystem* UDZITemSoundSystem::Get(const UObject* InWorldContextObject)
{
	if (!IsValid(InWorldContextObject)) return nullptr;
	
	UWorld* World = InWorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
			
	UGameInstance* GameInstance = World->GetGameInstance();

	UDZITemSoundSystem* ItemDataSubSystem = GameInstance->GetSubsystem<UDZITemSoundSystem>();
	if (!IsValid(ItemDataSubSystem)) return nullptr;

	return ItemDataSubSystem;
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

void UDZITemSoundSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// 데이터 초기화
	ItemPickUpSoundDataMap.Empty();
	ItemDropSoundDataMap.Empty();
	
	// 데이터 배열 공간 확보
	ItemPickUpSoundDataMap.Reserve(100);
	ItemDropSoundDataMap.Reserve(100);
	
	// 정적 데이터 테이블 캐싱 실시 
	UDZItemSoundSystemCachingHelperLibrary::CacheItemPickUpSoundDataTable_Lib(ItemPickUpSoundDataMap);
	UDZItemSoundSystemCachingHelperLibrary::CacheItemDropSoundTable_Lib(ItemDropSoundDataMap);
}

#pragma endregion
//======================================================================================================================	