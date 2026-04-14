// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyPlayLoopSound.h"

#include "Components/AudioComponent.h"
#include "FOR_INGAME/SECTION_GAS/Interface/DZCueVIsualInterface.h"
#include "Kismet/GameplayStatics.h"


ADZGCN_AnomalyPlayLoopSound::ADZGCN_AnomalyPlayLoopSound()
{
	bAutoDestroyOnRemove = true;
	bAutoAttachToOwner = false;
}

bool ADZGCN_AnomalyPlayLoopSound::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnActive_Implementation(MyTarget, Parameters);

	if (!IsValid(AudioComponent))
	{
		return false;
	}

	// 스폰 후 타겟 액터에 부착
	SpawnAndAttachLoopSound_internal(MyTarget, Parameters);

	return true;
}

bool ADZGCN_AnomalyPlayLoopSound::WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::WhileActive_Implementation(MyTarget, Parameters);

	// 늦게 접속한 클라이언트는 OnActive를 받지 못하므로 여기서 재생 보장
	if (!IsValid(AudioComponent))
	{
		SpawnAndAttachLoopSound_internal(MyTarget, Parameters);
		return true;
	}

	if (!AudioComponent->IsPlaying())
	{
		AudioComponent->Play();
	}

	return true;
}

bool ADZGCN_AnomalyPlayLoopSound::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnRemove_Implementation(MyTarget, Parameters);
	if (IsValid(AudioComponent) && AudioComponent->IsPlaying())
	{
		AudioComponent->Stop();
	}

	return true;
}

bool ADZGCN_AnomalyPlayLoopSound::SpawnAndAttachLoopSound_internal(AActor* MyTarget,
                                                                   const FGameplayCueParameters& Parameters)
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
	FDZLoopSoundCueData LoopSoundCueData;
	for (auto& Tag : Parameters.AggregatedSourceTags)
	{
		if (MyTargetInterface->GetLoopSoundCueData(Tag, LoopSoundCueData))
		{
			// 움직이는 메시 따라가도록 스폰 후 부착
			AudioComponent = UGameplayStatics::SpawnSoundAttached(
				LoopSoundCueData.LoopSound,
				MyTarget->GetRootComponent(),
				NAME_None,
				FVector::ZeroVector,
				EAttachLocation::SnapToTarget,
				true,
				1.f, 1.f, 0,
				LoopSoundCueData.Attenuation
			);
			return true;
		}
	}
	return false;
}
