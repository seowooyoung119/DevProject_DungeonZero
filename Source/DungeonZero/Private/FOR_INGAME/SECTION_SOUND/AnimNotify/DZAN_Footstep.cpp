// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/AnimNotify/DZAN_Footstep.h"

#include "FOR_INGAME/SECTION_SOUND/Comp/DZFootstepSoundComponent.h"

void UDZAN_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                            const FAnimNotifyEventReference& EventReference)
{
	// UDZFootstepSoundComponent의 PlayFootstepSound 함수 실행
	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}
	UDZFootstepSoundComponent* FootstepComp = MeshComp->GetOwner()->FindComponentByClass<UDZFootstepSoundComponent>();
	if (FootstepComp)
	{
		FVector SocketLocation = MeshComp->GetSocketLocation(SocketName);
		FootstepComp->PlayFootstepSound(SocketLocation, bIsLeft);
	}
}
