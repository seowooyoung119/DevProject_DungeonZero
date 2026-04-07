// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyAttachNiagara.h"

#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/DZGameplayCueTag.h"
#include "FOR_INGAME/SECTION_GAS/Interface/DZCueVIsualInterface.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

//======================================================================================================================	
#pragma region 라이프_사이클

//━━━━━━━━━━━━━━━━━━━━
// 라이프 사이클
//━━━━━━━━━━━━━━━━━━━━	
ADZGCN_AnomalyAttachNiagara::ADZGCN_AnomalyAttachNiagara()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ADZGCN_AnomalyAttachNiagara::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// DZCueVisualInterface 상속 받은 액터만 진행
	if (!MyTarget->Implements<UDZCueVIsualInterface>())
	{
		return false;
	}
	IDZCueVIsualInterface* MyTargetInterface = Cast<IDZCueVIsualInterface>(MyTarget);
	// 나이아가라 컴포넌트 부착
	TArray<FDZNiagaraCueData> NiagaraCueData;
	for (auto& Tag : Parameters.AggregatedSourceTags)
	{
		if (MyTargetInterface->GetNiagaraCueData(Tag, NiagaraCueData))
		{
			for (auto& CueData : NiagaraCueData)
			{
				ApplyNiagara(MyTarget, CueData);
			}
		}
	}
	return true;
}

bool ADZGCN_AnomalyAttachNiagara::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (CachedNiagaraEffects.Num() == 0)
	{
		return false;
	}
	// 나이아가라 이펙트 비활성화
	for (auto& NiagaraEffect : CachedNiagaraEffects)
	{
		if (NiagaraEffect)
		{
			NiagaraEffect->Deactivate();
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
void ADZGCN_AnomalyAttachNiagara::ApplyNiagara(AActor* MyTarget, FDZNiagaraCueData& CueData)
{
	// 태그로 타겟 메시 찾기
	for (auto& TargetMesh : MyTarget->GetComponentsByTag(UStaticMeshComponent::StaticClass(), CueData.TargetMeshTag))
	{
		UStaticMeshComponent* TargetStaticMesh = CastChecked<UStaticMeshComponent>(TargetMesh);

		for (auto& SocketName : TargetStaticMesh->GetAllSocketNames())
		{
			// 접두사로 시작하는 소켓만 진행
			if (!SocketName.ToString().StartsWith(CueData.SocketNamePrefix.ToString()))
			{
				continue;
			}
			// 소켓 트랜스폼에 맞게 스폰 후 부착
			UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
				CueData.NiagaraSystem,
				TargetStaticMesh,
				SocketName,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				EAttachLocation::SnapToTargetIncludingScale,
				false,
				true
			);
			// 나이아가라 컴포넌트 저장, On_Remove에서 비활성화
			CachedNiagaraEffects.Add(NiagaraComponent);
		}
	}
}
#pragma endregion
//======================================================================================================================	
