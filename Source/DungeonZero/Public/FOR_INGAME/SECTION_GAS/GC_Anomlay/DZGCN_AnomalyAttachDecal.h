// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyAttachDecal.generated.h"

struct FDZDecalCueData;

UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyAttachDecal : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	
	ADZGCN_AnomalyAttachDecal();
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	
#pragma endregion
	//======================================================================================================================	
#pragma region 내부 함수

	//━━━━━━━━━━━━━━━━━━━━
	// 내부 함수
	//━━━━━━━━━━━━━━━━━━━━		
protected:
	void ApplyDecal(AActor* MyTarget, FDZDecalCueData& CueData);
	
	// 어노말리 액터에 부착된 나이아가라 컴포넌트 캐싱
	UPROPERTY()
	TArray<TObjectPtr<AActor>> CachedDecal;
#pragma endregion
	//======================================================================================================================	
};
