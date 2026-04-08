// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_VFX/FootStep/AnimNotify/DZAN_AnomalyFootStepVFX.h"
#include "FOR_INGAME/SECTION_VFX/FootStep/Comp/DZAnomalyFootstepVFXComponent.h"

void UDZAN_AnomalyFootStepVFX::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	// PlayFootstepVFX 함수 실행
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner()))
	{
		return;
	}
	
	UDZAnomalyFootstepVFXComponent* FootstepVFXComp = MeshComp->GetOwner()->FindComponentByClass<UDZAnomalyFootstepVFXComponent>();
	if (IsValid(FootstepVFXComp))
	{
		FVector SocketLocation = MeshComp->GetSocketLocation(SocketName);
		FRotator SocketRotation = MeshComp->GetSocketRotation(SocketName);
		FootstepVFXComp->PlayFootstepVFX(SocketLocation, SocketRotation, bIsLeft);
	}
}
