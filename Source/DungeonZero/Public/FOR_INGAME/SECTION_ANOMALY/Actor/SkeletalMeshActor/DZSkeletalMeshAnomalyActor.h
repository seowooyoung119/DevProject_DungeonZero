// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "DZSkeletalMeshAnomalyActor.generated.h"

class USkeletalMeshComponent;

UCLASS()
class DUNGEONZERO_API ADZSkeletalMeshAnomalyActor : public ADZAnomalyActorBase
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클 
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZSkeletalMeshAnomalyActor();

#pragma endregion
//======================================================================================================================	
#pragma region 컴포넌트
	
	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트 
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | AnomalyActor")
	TObjectPtr<USkeletalMeshComponent> MainMeshComp = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
