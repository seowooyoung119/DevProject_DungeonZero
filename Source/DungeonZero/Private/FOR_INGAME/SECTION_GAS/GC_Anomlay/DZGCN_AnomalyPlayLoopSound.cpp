// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyPlayLoopSound.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


ADZGCN_AnomalyPlayLoopSound::ADZGCN_AnomalyPlayLoopSound()
{
	bAutoDestroyOnRemove = true;
	bAutoAttachToOwner = false;
}

bool ADZGCN_AnomalyPlayLoopSound::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnActive_Implementation(MyTarget, Parameters);

	if (!IsValid(AudioComponent) || !IsValid(LoopSound))
	{
		return false;
	}

	// 스폰 후 타겟 액터에 부착
	SpawnAndAttachSound_internal(MyTarget);
	
	return true;
}

bool ADZGCN_AnomalyPlayLoopSound::WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::WhileActive_Implementation(MyTarget, Parameters);
	
	// 늦게 접속한 클라이언트는 OnActive를 받지 못하므로 여기서 재생 보장
	if (!IsValid(AudioComponent))
	{
		SpawnAndAttachSound_internal(MyTarget);
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

void ADZGCN_AnomalyPlayLoopSound::SpawnAndAttachSound_internal(AActor* MyTarget)
{
	// 움직이는 메시 따라가도록 스폰 후 부착
	AudioComponent = UGameplayStatics::SpawnSoundAttached(
		LoopSound,
		MyTarget->GetRootComponent(),
		NAME_None,
		FVector::ZeroVector,
		EAttachLocation::SnapToTarget,
		true
	);
}
