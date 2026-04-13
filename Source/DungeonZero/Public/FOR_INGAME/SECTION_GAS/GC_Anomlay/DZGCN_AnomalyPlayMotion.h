// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyPlayMotion.generated.h"

UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyPlayMotion : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZGCN_AnomalyPlayMotion();
	
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

#pragma endregion
//======================================================================================================================
};
