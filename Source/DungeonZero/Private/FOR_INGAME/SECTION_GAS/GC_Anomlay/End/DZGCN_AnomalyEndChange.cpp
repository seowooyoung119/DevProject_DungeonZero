// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/End/DZGCN_AnomalyEndChange.h"
#include "FOR_INGAME/SECTION_ANOMALY/Interface/DZAnomalySealAdditionalFunction.h"
#include "Kismet/GameplayStatics.h"

ADZGCN_AnomalyEndChange::ADZGCN_AnomalyEndChange()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ADZGCN_AnomalyEndChange::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// 1. AvatarActor가 유효 체크
	AActor* AvatarActor = MyTarget;
	if (IsValid(AvatarActor))
	{
		// 2. 인터페이스를 구현했는지 체크
		if (AvatarActor->GetClass()->ImplementsInterface(UDZAnomalySealAdditionalFunction::StaticClass()))
		{
			// 3. 엔딩 함수 call
			IDZAnomalySealAdditionalFunction::Execute_AnomalySealAdditionalFunction(AvatarActor);
			
			// 4. 사운드 call
			if (IsValid(ReturnSound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReturnSound, AvatarActor->GetActorLocation());
			}
		}
	}
	
	return true;
}


