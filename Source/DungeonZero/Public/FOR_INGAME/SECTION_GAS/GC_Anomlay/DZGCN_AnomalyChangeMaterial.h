// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyChangeMaterial.generated.h"

struct FDZMaterialCueData;

UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyChangeMaterial : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	
	ADZGCN_AnomalyChangeMaterial();
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 내부 함수

	//━━━━━━━━━━━━━━━━━━━━
	// 내부 함수
	//━━━━━━━━━━━━━━━━━━━━		
protected:
	void ApplyAnomalyMaterial(AActor* MyTarget, FDZMaterialCueData& CueData);
	void ApplyOriginalMaterial(AActor* MyTarget, FDZMaterialCueData& CueData);
	// 어노말리 액터의 머티리얼 데이터 캐싱
	UPROPERTY()
	TArray<FDZMaterialCueData> CachedMaterialCueData;
#pragma endregion
//======================================================================================================================	
};
