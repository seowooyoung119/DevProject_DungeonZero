// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/SkeletalMeshActor/DZSkeletalMeshAnomalyActor.h"
#include "DZAnomalyShadow.generated.h"

UCLASS()
class DUNGEONZERO_API ADZAnomalyShadow : public ADZSkeletalMeshAnomalyActor
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

public:
	ADZAnomalyShadow();
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 어노말리_엔딩_펑션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리 엔딩 펑션
	//━━━━━━━━━━━━━━━━━━━━	
public:
	virtual void AnomalySealAdditionalFunction_Implementation() override { DisovleShadow(); };

protected:
	// 해골 그림자 디졸브로 되돌림
	UFUNCTION(BlueprintImplementableEvent)
	void DisovleShadow();

#pragma endregion
//======================================================================================================================	
		
};
