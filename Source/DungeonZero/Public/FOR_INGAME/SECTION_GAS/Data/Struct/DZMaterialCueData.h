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
	
	// 복원용 원본 머티리얼
	UPROPERTY(BlueprintReadWrite, Category = "DZ | Cue | Material")
	TObjectPtr<UMaterialInterface> OriginalMaterial = nullptr;
};

// 타겟 메시 머티리얼 오버라이드 데이터
USTRUCT(BlueprintType)
struct FDZMaterialCueData
{
	GENERATED_BODY()

	// 타겟 메시 컴포넌트 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Material")
	FName TargetMeshTag = "MainMesh";
	
	// 머티리얼 슬롯 오버라이드 데이터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Material")
	TArray<FDZMaterialSlotOverride> SlotOverrides;
};

// 머티리얼 오버라이드 데이터 배열 구조체
USTRUCT(BlueprintType)
struct FDZMaterialCueDataArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Material")
	TArray<FDZMaterialCueData> MaterialCueDataArray;
};