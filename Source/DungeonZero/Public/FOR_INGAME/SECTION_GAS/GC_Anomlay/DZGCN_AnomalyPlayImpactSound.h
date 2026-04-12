// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "DZGCN_AnomalyPlayImpactSound.generated.h"

UCLASS()
class DUNGEONZERO_API UDZGCN_AnomalyPlayImpactSound : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	UDZGCN_AnomalyPlayImpactSound();
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
	                               const FGameplayCueParameters& Parameters) override;

#pragma endregion
//======================================================================================================================	
};
