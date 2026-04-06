// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyAttachDecal.h"

#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/DZGameplayCueTag.h"
#include "FOR_INGAME/SECTION_GAS/Interface/DZCueVIsualInterface.h"

//======================================================================================================================	
#pragma region 라이프_사이클

//━━━━━━━━━━━━━━━━━━━━
// 라이프 사이클
//━━━━━━━━━━━━━━━━━━━━	
ADZGCN_AnomalyAttachDecal::ADZGCN_AnomalyAttachDecal()
{
	PrimaryActorTick.bCanEverTick = false;
	//GameplayCueTag = DZ::GameplayCue::DZ_CUE_ANOMALY_DECAL;
}

bool ADZGCN_AnomalyAttachDecal::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// DZCueVisualInterface 상속 받은 액터만 진행
	if (!MyTarget->Implements<UDZCueVIsualInterface>())
	{
		return false;
	}
	IDZCueVIsualInterface* MyTargetInterface = Cast<IDZCueVIsualInterface>(MyTarget);
	// 데칼 부착
	TArray<FDZDecalCueData> DecalCueData;
	for (auto& Tag : Parameters.AggregatedSourceTags)
	{
		if (MyTargetInterface->GetDecalCueData(Tag, DecalCueData))
		{
			for (auto& CueData : DecalCueData)
			{
				ApplyDecal(MyTarget, CueData);
			}
		}
	}
	return true;
}

bool ADZGCN_AnomalyAttachDecal::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (CachedDecal.Num() == 0)
	{
		return false;
	}
	// 데칼 삭제
	for (auto& Decal : CachedDecal)
	{
		if (IsValid(Decal))
		{
			Decal->Destroy();
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
void ADZGCN_AnomalyAttachDecal::ApplyDecal(AActor* MyTarget, FDZDecalCueData& CueData)
{
	UWorld* World = GetWorld();
	// 태그로 타겟 메시 찾기
	for (auto& TargetMesh : MyTarget->GetComponentsByTag(UStaticMeshComponent::StaticClass(), CueData.TargetMeshTag))
	{
		UStaticMeshComponent* TargetStaticMesh = CastChecked<UStaticMeshComponent>(TargetMesh);
		// 데칼 스폰해서 소켓에 부착 
		if (const UStaticMeshSocket* Socket = TargetStaticMesh->GetSocketByName(CueData.SocketName))
		{
			FTransform SocketTransform = TargetStaticMesh->GetSocketTransform(CueData.SocketName);
			
			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AActor* SpawnedDecal = GetWorld()->SpawnActorDeferred<AActor>(
				CueData.DecalClass,
				SocketTransform,
				nullptr,
				nullptr,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

			if (SpawnedDecal)
			{
				SpawnedDecal->AttachToComponent(
					TargetStaticMesh,
					FAttachmentTransformRules::SnapToTargetIncludingScale,
					CueData.SocketName
				);

				SpawnedDecal->FinishSpawning(SocketTransform);
				CachedDecal.Add(SpawnedDecal);
			}
		}
	}
}
#pragma endregion
//======================================================================================================================	
