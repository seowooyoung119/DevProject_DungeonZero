// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZInteractData.generated.h"

USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZInteractData
{
	GENERATED_BODY()
	
	// 상호작용을 일으킨 액터
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Interact")
	TObjectPtr<AActor> Instigator = nullptr;
	
};
