// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DZItemTablesDataAsset.generated.h"

class UDataTable;
/**
 * 아이템 데이터 테이블
 */
UCLASS()
class DUNGEONZERO_API UTSItemTablesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// 아이템 기본 정보 테이블 모음
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TS | Item")
	TObjectPtr<UDataTable> ItemInfoTable;

};