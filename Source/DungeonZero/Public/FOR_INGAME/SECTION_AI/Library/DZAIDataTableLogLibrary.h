// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_AI/Data/Table/DZAIClassTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZAIDataTableLogLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAIDataTableLogLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// 정적 데이터 로그 
	static void LogAIData_Lib(const FDZAIClassTable* InAIClassTable);
	
};
