// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_VFX/FootStep/Comp/DZAnomalyFootstepVFXComponent.h"


//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZAnomalyFootstepVFXComponent::UDZAnomalyFootstepVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	

void UDZAnomalyFootstepVFXComponent::PlayFootstepVFX(const FVector& SocketLocation, const FRotator& CharacterRotation, bool& bIsLeft)
{
	Super::PlayFootstepVFX(SocketLocation, CharacterRotation, bIsLeft);	
}

void UDZAnomalyFootstepVFXComponent::OnLandedVFX(const FHitResult& Hit)
{
	Super::OnLandedVFX(Hit);
}

#pragma endregion
//======================================================================================================================	