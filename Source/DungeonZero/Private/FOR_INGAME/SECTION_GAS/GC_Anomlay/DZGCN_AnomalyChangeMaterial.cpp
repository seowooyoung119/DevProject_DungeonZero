// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyChangeMaterial.h"

#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/DZGameplayCueTag.h"
#include "FOR_INGAME/SECTION_GAS/Interface/DZCueVIsualInterface.h"

//======================================================================================================================	
#pragma region 라이프_사이클

//━━━━━━━━━━━━━━━━━━━━
// 라이프 사이클
//━━━━━━━━━━━━━━━━━━━━	
ADZGCN_AnomalyChangeMaterial::ADZGCN_AnomalyChangeMaterial()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ADZGCN_AnomalyChangeMaterial::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// DZCueVisualInterface 상속 받은 액터만 진행
	if (!MyTarget->Implements<UDZCueVIsualInterface>())
	{
		return false;
	}
	IDZCueVIsualInterface* MyTargetInterface = Cast<IDZCueVIsualInterface>(MyTarget);
	// 어노말리 머티리얼 오버라이드
	for (auto& Tag : Parameters.AggregatedSourceTags)
	{
		if (MyTargetInterface->GetMaterialCueData(Tag, CachedMaterialCueData))
		{
			for (auto& MaterialData : CachedMaterialCueData)
			{
				ApplyAnomalyMaterial(MyTarget, MaterialData);
			}
		}
	}
	return true;
}

bool ADZGCN_AnomalyChangeMaterial::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (CachedMaterialCueData.Num() == 0)
	{
		return false;
	}
	if (!IsValid(MyTarget))
	{
		return false;
	}
	// 원본 머티리얼로 복원
	for (auto& MaterialData : CachedMaterialCueData)
	{
		if (IsValid(MyTarget))
		{
			ApplyOriginalMaterial(MyTarget, MaterialData);
		}
	}
	return true;
}
#pragma endregion
//======================================================================================================================	
#pragma region 내부 함수

//━━━━━━━━━━━━━━━━━━━━
// 내부 함수
//━━━━━━━━━━━━━━━━━━━━	
void ADZGCN_AnomalyChangeMaterial::ApplyAnomalyMaterial(AActor* MyTarget, FDZMaterialCueData& CueData)
{
	// 태그로 타겟 메시 컴포넌트 찾기 
	UStaticMeshComponent* TargetMesh = Cast<UStaticMeshComponent>(
		MyTarget->FindComponentByTag(UStaticMeshComponent::StaticClass(), CueData.TargetMeshTag));
	if (!IsValid(TargetMesh))
	{
		return;
	}
	// 해당 타겟 메시의 머티리얼 변경
	for (auto& SlotOverride : CueData.SlotOverrides)
	{
		// 원본 머티리얼 저장
		SlotOverride.OriginalMaterial = TargetMesh->GetMaterial(SlotOverride.SlotIndex);
		// 어노말리 머티리얼로 변경
		TargetMesh->SetMaterial(SlotOverride.SlotIndex, SlotOverride.OverrideMaterial);
	}
}

void ADZGCN_AnomalyChangeMaterial::ApplyOriginalMaterial(AActor* MyTarget, FDZMaterialCueData& CueData)
{
	// 태그로 타겟 메시 컴포넌트 찾기 
	UStaticMeshComponent* TargetMesh = Cast<UStaticMeshComponent>(
		MyTarget->FindComponentByTag(UStaticMeshComponent::StaticClass(), CueData.TargetMeshTag));
	if (!IsValid(TargetMesh))
	{
		return;
	}
	// 해당 타겟 메시의 머티리얼 변경
	for (auto& SlotOverride : CueData.SlotOverrides)
	{
		// 원본 머티리얼로 복원
		TargetMesh->SetMaterial(SlotOverride.SlotIndex, SlotOverride.OriginalMaterial);
	}
}
#pragma endregion
//======================================================================================================================	
