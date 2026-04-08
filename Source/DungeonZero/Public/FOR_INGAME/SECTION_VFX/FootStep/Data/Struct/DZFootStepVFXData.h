// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "DZFootStepVFXData.generated.h"

USTRUCT(BlueprintType)
struct FDZFootstepVFXData
{
	GENERATED_BODY()

	// 발자국 먼지/물방울 등 나이아가라 이펙트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraSystem> FootstepParticle = nullptr;

	// 오른 발자국 데칼 (텍스처)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
	TObjectPtr<UMaterialInterface> RightFootstepDecal = nullptr;

	// 왼 발자국 데칼 (텍스처)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
	TObjectPtr<UMaterialInterface> LeftFootstepDecal = nullptr;
	
	// 오른발 보정 각도 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
	float DecalRotation_Right = 0.f;

	// 왼발 보정 각도 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
	float DecalRotation_Left = 0.f;	
	
	// 데칼 크기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
	FVector DecalSize = FVector(8.f, 16.f, 16.f);

	// 데칼 유지 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal")
	float DecalLifeSpan = 10.f;
};