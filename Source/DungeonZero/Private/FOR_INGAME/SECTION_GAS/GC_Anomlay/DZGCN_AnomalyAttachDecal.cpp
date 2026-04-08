// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyAttachDecal.h"

#include "Engine/StaticMeshSocket.h"
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
}

bool ADZGCN_AnomalyAttachDecal::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// DZCueVisualInterface 상속 받은 액터만 진행
	if (!MyTarget->Implements<UDZCueVIsualInterface>())
	{
		return false;
	}

	IDZCueVIsualInterface* MyTargetInterface = Cast<IDZCueVIsualInterface>(MyTarget);
	if (!MyTargetInterface)
	{
		return false;
	}
	// 리시브 데칼 활성화
	MyTargetInterface->SetRecieveDecals(true);
	
	// 데칼 부착
	TArray<FDZDecalCueData> DecalCueData;
	for (auto& Tag : Parameters.AggregatedSourceTags)
	{
		if (MyTargetInterface->GetDecalCueData(Tag, DecalCueData))
		{
			for (auto& CueData : DecalCueData)
			{
				if (IsValid(MyTarget))
				{
					ApplyDecal(MyTarget, CueData);
				}
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
	if (!IsValid(MyTarget) || !MyTarget->Implements<UDZCueVIsualInterface>())
	{
		return false;
	}
	// 리시브 데칼 비활성화
	if (IDZCueVIsualInterface* MyTargetInterface = Cast<IDZCueVIsualInterface>(MyTarget))
	{
		MyTargetInterface->SetRecieveDecals(false);
	}
	// 데칼 삭제
	for (auto& Decal : CachedDecal)
	{
		if (Decal.IsValid() && IsValid(Decal.Get()))
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
	if (!IsValid(World)) return;

	// 태그로 타겟 메시 찾기
	for (auto& TargetMesh : MyTarget->GetComponentsByTag(UStaticMeshComponent::StaticClass(), CueData.TargetMeshTag))
	{
		if (!IsValid(TargetMesh)) continue;

		UStaticMeshComponent* TargetStaticMesh = CastChecked<UStaticMeshComponent>(TargetMesh);
		if (!IsValid(TargetStaticMesh)) continue;
		
		// 데칼 스폰해서 소켓에 부착 
		const UStaticMeshSocket* Socket = TargetStaticMesh->GetSocketByName(CueData.SocketName);
		if (!Socket->IsValidLowLevel()) continue;

		FTransform SocketTransform = TargetStaticMesh->GetSocketTransform(CueData.SocketName);

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* SpawnedDecal = GetWorld()->SpawnActorDeferred<AActor>(CueData.DecalClass, SocketTransform, nullptr,
		                                                              nullptr,
		                                                              ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if (!IsValid(SpawnedDecal)) continue;

		SpawnedDecal->AttachToComponent(TargetStaticMesh, FAttachmentTransformRules::SnapToTargetIncludingScale,
		                                CueData.SocketName);
		SpawnedDecal->FinishSpawning(SocketTransform);
		CachedDecal.Add(SpawnedDecal);
	}
}
#pragma endregion
//======================================================================================================================	
