// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "DZPhysicsImpactData.generated.h"

// Hit 이벤트 시 부착할 데이터
USTRUCT(BlueprintType)
struct FDZPhysicsImpactData
{
	GENERATED_BODY()
	
	// 부착할 데칼 액터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | PhysicsImpact")
	TSubclassOf<AActor> DecalClass = nullptr;
	// 부착할 나이아가라
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | PhysicsImpact")
	TSubclassOf<UNiagaraSystem> NiagaraSystem = nullptr;
};
