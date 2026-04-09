// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GameplayCueNotify_Static.h"
#include "DZGCN_AnomalyEndShadowDisovle.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyEndShadowDissolve : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
public:
	ADZGCN_AnomalyEndShadowDissolve();
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDZGCN_AnomalyEndShadowDisovle")
	TObjectPtr<USoundBase> DissolveSound = nullptr;

};
