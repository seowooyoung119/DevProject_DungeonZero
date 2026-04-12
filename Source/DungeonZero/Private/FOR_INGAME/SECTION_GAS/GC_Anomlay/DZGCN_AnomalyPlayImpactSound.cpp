// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyPlayImpactSound.h"

#include "FOR_INGAME/SECTION_ANOMALY/Comp/DZAnomalyPhysicsImpactComponent.h"
#include "FOR_INGAME/SECTION_SOUND/FootStep/Data/Asset/DZAnomalySoundDataAsset.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
UDZGCN_AnomalyPlayImpactSound::UDZGCN_AnomalyPlayImpactSound()
{
}

void UDZGCN_AnomalyPlayImpactSound::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
	const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
	UDZAnomalyPhysicsImpactComponent* ImpactComponent = Cast<UDZAnomalyPhysicsImpactComponent>(
		MyTarget->GetComponentByClass(UDZAnomalyPhysicsImpactComponent::StaticClass()));
	if (!IsValid(ImpactComponent))
	{
		return;
	}
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();
	if (!HitResult)
	{
		return;
	}
	for (auto& GATag : Parameters.AggregatedSourceTags)
	{
		
		TObjectPtr<USoundBase> Sound = ImpactComponent->GetImpactSound(*HitResult);
		if (IsValid(Sound))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, HitResult->ImpactPoint, FRotator::ZeroRotator,
												  1.f, 1.f, 0.f,
												  ImpactComponent->ImpactSoundDataAsset->DefaultAttenuation,
												  ImpactComponent->ImpactSoundDataAsset->DefaultConcurrency);
		}
	}
}
