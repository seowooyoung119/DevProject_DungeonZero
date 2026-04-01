// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "DZNiagaraCueData.generated.h"

USTRUCT(BlueprintType)
struct FDZNiagaraCueData
{
	GENERATED_BODY()

	// 재생할 나이아가라 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ|Cue")
	TObjectPtr<UNiagaraSystem> NiagaraSystem = nullptr;

	// 소켓 필터링 접두사 (예: "FirePoint", "SmokePoint")
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ|Cue")
	FName SocketNamePrefix = NAME_None;
};
