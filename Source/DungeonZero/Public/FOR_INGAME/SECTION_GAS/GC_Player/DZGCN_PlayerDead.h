// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_PlayerDead.generated.h"

UCLASS()
class DUNGEONZERO_API ADZGCN_PlayerDead : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	ADZGCN_PlayerDead();
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
};
