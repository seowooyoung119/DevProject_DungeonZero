// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyEndCeilingEyesFall.generated.h"

UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyEndCeilingEyesFall : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
public:
	ADZGCN_AnomalyEndCeilingEyesFall();
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ADZGCN_AnomalyEndCeilingEyesFall")
	TObjectPtr<USoundBase> FallSound = nullptr;

};
