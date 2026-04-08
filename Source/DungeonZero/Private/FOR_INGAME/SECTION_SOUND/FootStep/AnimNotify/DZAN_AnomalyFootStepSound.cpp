// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/FootStep/AnimNotify/DZAN_AnomalyFootStepSound.h"
#include "FOR_INGAME/SECTION_SOUND/FootStep/Comp/DZAnomalyFootStepSoundComponent.h"

void UDZAN_AnomalyFootStepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	// PlayFootstepSound 함수 실행
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner()))
	{
		return;
	}
	UDZAnomalyFootStepSoundComponent* FootstepComp = MeshComp->GetOwner()->FindComponentByClass<UDZAnomalyFootStepSoundComponent>();
	if (IsValid(FootstepComp))
	{
		FVector SocketLocation = MeshComp->GetSocketLocation(SocketName);
		FootstepComp->PlayFootstepSound(SocketLocation, bIsLeft);
	}
}
