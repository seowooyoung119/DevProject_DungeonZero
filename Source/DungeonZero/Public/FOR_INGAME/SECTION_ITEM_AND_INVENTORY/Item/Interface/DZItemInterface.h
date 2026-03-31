// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZItemRuntimeData.h"
#include "UObject/Interface.h"
#include "DZItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class DUNGEONZERO_API UDZItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONZERO_API IDZItemInterface
{
	GENERATED_BODY()

public:
	// 아이템 데이터 포인터 가져오기
	virtual FDZItemRuntimeData& GetItemRuntimeDataPtr() = 0;
	// 아이템 데이터 주입 
	virtual void SetItemRuntimeData(FDZItemRuntimeData& InItemRuntimeData) = 0;
};
