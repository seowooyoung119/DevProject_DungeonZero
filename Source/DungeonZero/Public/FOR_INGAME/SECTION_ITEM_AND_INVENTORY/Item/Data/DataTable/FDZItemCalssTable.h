// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataTable.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FDZItemCalssTable.generated.h"

USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZItemClassTable : public FTableRowBase
{
	GENERATED_BODY()
	
	// 아이템 ID 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	int32 ItemID = -1;
	
	// 아이템 클래스 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	TSubclassOf<ADZItemActorBase> ItemClass = nullptr;
	
	// 아이템 사용 시 발동 어빌리티 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	TSubclassOf<UGameplayAbility> ItemGA = nullptr; 
};
