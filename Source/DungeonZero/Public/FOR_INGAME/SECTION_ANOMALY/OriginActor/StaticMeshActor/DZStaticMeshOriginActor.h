// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/OriginActor/Base/DZOriginActorBase.h"
#include "DZStaticMeshOriginActor.generated.h"

UCLASS()
class DUNGEONZERO_API ADZStaticMeshOriginActor : public ADZOriginActorBase
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클 
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZStaticMeshOriginActor();

#pragma endregion
//======================================================================================================================
#pragma region 컴포넌트
	
	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트 
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | AnomalyActor")
	TObjectPtr<UStaticMeshComponent> MainMeshComp = nullptr;
	
#pragma endregion
//======================================================================================================================
};
