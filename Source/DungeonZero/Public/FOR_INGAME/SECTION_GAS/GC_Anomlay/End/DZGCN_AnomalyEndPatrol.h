// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyEndPatrol.generated.h"

UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyEndPatrol : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADZGCN_AnomalyEndPatrol();
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDZGCN_AnomalyEndShadowDisovle")
	TObjectPtr<USoundBase> DissolveSound = nullptr;
};
