// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/FootStep/AnimNotify/DZAN_PlayerFootstepSound.h"
#include "FOR_INGAME/SECTION_SOUND/FootStep/Comp/DZPlayerFootstepSoundComponent.h"

void UDZAN_PlayerFootstepSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// PlayFootstepSound 함수 실행
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner()))
	{
		return;
	}
	UDZPlayerFootstepSoundComponent* FootstepComp = MeshComp->GetOwner()->FindComponentByClass<UDZPlayerFootstepSoundComponent>();
	if (IsValid(FootstepComp))
	{
		FVector SocketLocation = MeshComp->GetSocketLocation(SocketName);
		FootstepComp->PlayFootstepSound(SocketLocation, bIsLeft);
	}
}
