// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FOR_INGAME/SECTION_VFX/FootStep/Data/Struct/DZFootStepVFXData.h"
#include "DZFootStepVFXDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZFootStepVFXDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	// 표면별 VFX 데이터 맵
	UPROPERTY(EditDefaultsOnly, Category = "DZ | VFX")
	TMap<TEnumAsByte<EPhysicalSurface>, FDZFootstepVFXData> SurfaceVFXMap = {};

	// 기본 VFX 데이터
	UPROPERTY(EditDefaultsOnly, Category = "DZ | VFX")
	FDZFootstepVFXData DefaultVFXData = FDZFootstepVFXData();

};
