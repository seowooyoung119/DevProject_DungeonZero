// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "DZGCN_PickItem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGCN_PickItem : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	UDZGCN_PickItem();
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const override;
};
