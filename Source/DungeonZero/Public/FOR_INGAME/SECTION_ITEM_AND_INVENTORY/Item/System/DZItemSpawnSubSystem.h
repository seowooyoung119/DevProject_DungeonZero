// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZItemRuntimeData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DZItemSpawnSubSystem.generated.h"

class ADZItemActorBase;
/**
 * 아이템 스폰을 도와주는 헬퍼 시스템
 */
UCLASS()
class DUNGEONZERO_API UDZItemSpawnSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	
public:

	static UDZItemSpawnSubSystem* Get(const UObject* InWorldContextObject);
	
#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부 API
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	// 새로운 아이템 생성할 때 호출 
	ADZItemActorBase* SpawnNewItem(int32 InSpawnItemID, int32 InWantStackSize, FVector& InSpawnLocation, FRotator& InSpawnRotation);	
	// 기존 아이템 드랍할 때 호출
	ADZItemActorBase* DropItemFromSomeWhere(FDZItemRuntimeData& InItemRuntimeData, FVector& InDropLocation, FRotator& InDropRotation);
	
#pragma endregion
//======================================================================================================================		
};
