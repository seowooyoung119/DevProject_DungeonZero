// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/End/DZGCN_AnomalyEndShadowDisovle.h"
#include "FOR_INGAME/SECTION_ANOMALY/Interface/DZAnomalySealAdditionalFunction.h"
#include "Kismet/GameplayStatics.h"

UDZGCN_AnomalyEndShadowDissolve::UDZGCN_AnomalyEndShadowDissolve()
{
}

bool UDZGCN_AnomalyEndShadowDissolve::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
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
			if (IsValid(DissolveSound))
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), DissolveSound, AvatarActor->GetActorLocation());
			}
		}
	}
	
	return true;
}
