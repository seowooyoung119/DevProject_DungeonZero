// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZMaterialCueData.generated.h"

// 머티리얼 슬롯 단위 오버라이드 데이터 
USTRUCT(BlueprintType)
struct FDZMaterialSlotOverride
{
	GENERATED_BODY()

	// 오버라이드할 머티리얼 슬롯 인덱스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Material")
	int32 SlotIndex = 0;

	// 어노말리 활성화 시 적용할 머티리얼
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Material")
	TObjectPtr<UMaterialInterface> OverrideMaterial = nullptr;
};

// GameplayCueTag에 매핑할 머티리얼 오버라이드 데이터
USTRUCT(BlueprintType)
struct FDZMaterialCueData
{
	GENERATED_BODY()

	// 오버라이드 대상 메시 컴포넌트 이름
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ|Cue")
	FName MeshCompName = NAME_None;

	// 머티리얼 슬롯 오버라이드 데이터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ|Cue")
	TArray<FDZMaterialSlotOverride> SlotOverrides;
};