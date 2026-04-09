// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyEndFootPrintDisovle.generated.h"

UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyEndFootPrintDisovle : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	ADZGCN_AnomalyEndFootPrintDisovle();
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDZGCN_AnomalyEndShadowDisovle")
	TObjectPtr<USoundBase> DissolveSound = nullptr;

};
