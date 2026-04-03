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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Niagara")
	TObjectPtr<UNiagaraSystem> NiagaraSystem = nullptr;

	// 소켓 필터링 접두사 (예: "FirePoint", "SmokePoint")
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Niagara")
	FName SocketNamePrefix = NAME_None;
	
	// 타겟 메시 컴포넌트 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Niagara")
	FName TargetMeshTag = "MainMesh";
};

// 나이아가라 데이터 배열 구조체
USTRUCT(BlueprintType)
struct FDZNiagaraCueDataArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Niagara")
	TArray<FDZNiagaraCueData> NiagaraCueDataArray;
};