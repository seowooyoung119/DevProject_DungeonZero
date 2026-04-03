// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Enum/InventorySlotType/DZInventorySlotType.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Enum/InventoryType/DZInventoryCompType.h"
#include "DZItemInfoTable.generated.h"

class UGameplayAbility;
class ADZItemActorBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZItemInfoTable : public FTableRowBase
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 기본_정보
	
	//━━━━━━━━━━━━━━━━━━━━
	// 기본_정보
	//━━━━━━━━━━━━━━━━━━━━	
	
	// 아이템 ID 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	int32 ItemID = -1;
	
	// 아이템 클래스 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	TSubclassOf<AActor> ItemClass;
	
#pragma endregion
//======================================================================================================================	
#pragma region UI정보
	
	//━━━━━━━━━━━━━━━━━━━━
	// UI정보
	//━━━━━━━━━━━━━━━━━━━━
		
	// 아이템 아이콘 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TS | Item")
	TSoftObjectPtr<UTexture2D> ItemIcon;
	
	// 아이템 이름 (영어)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TS | Item")
	FText ItemName = FText::FromString(TEXT("No Name Edit"));
	
	// 아이템 설명 (영어)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TS | Item")
	FText ItemDescription = FText::FromString(TEXT("No Description Edit"));
	
	// 아이템 상호작용 키  (영어)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TS | Item")
	FText ItemInteractKeyType = FText::FromString(TEXT("No Key Type Edit"));
	
#pragma endregion
//======================================================================================================================	
#pragma region 인벤토리_정보
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인벤토리_정보
	//━━━━━━━━━━━━━━━━━━━━	
	
	// 들어갈 수 있는 인벤토리 타입 (기본값 : 플레이어 핫키, 가방 / AI 가방 / 보관함 / 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	TArray<EDZInventoryCompType> MatchInventoryCompType = { EDZInventoryCompType::PlayerHotKey };
	
	// 들어갈 수 있는 슬롯 타입 (기본값 : Common)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	TArray<EDZInventorySlotType> MatchInventorySlotType = { EDZInventorySlotType::Common };  
	
	// 최대 스택 가능한 갯수 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	int32 MaxStackSize = 1;
	
	// 핫키에서 어태치할 부분 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	FName HotKeyAttachSocketName =  NAME_None;
	
#pragma endregion
//======================================================================================================================	
#pragma region 아이템_어빌리티
	
	//━━━━━━━━━━━━━━━━━━━━
	// 아이템_어빌리티
	//━━━━━━━━━━━━━━━━━━━━	
	// 아이템 사용 시 발동 어빌리티 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " TS | Item")
	TSubclassOf<UGameplayAbility> ItemGA = nullptr; 
	
#pragma endregion
//======================================================================================================================	
};
