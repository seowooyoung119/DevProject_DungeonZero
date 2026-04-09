// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "DZGCN_AnomalyEndShadowDisovle.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGCN_AnomalyEndShadowDissolve : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	UDZGCN_AnomalyEndShadowDissolve();
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDZGCN_AnomalyEndShadowDisovle")
	TObjectPtr<USoundBase> DissolveSound = nullptr;

};
