// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "DZAnomalyChangeBase.generated.h"

UCLASS()
class DUNGEONZERO_API ADZAnomalyChangeBase : public ADZAnomalyActorBase
{
	GENERATED_BODY()

public:
	ADZAnomalyChangeBase();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<USceneComponent> RootScene = nullptr;
	
	// 원본과 변한 메쉬들
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UStaticMeshComponent> ChangeMeshComp = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UStaticMeshComponent> OriginMeshComp = nullptr;
	
};
