// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/FootStep/Comp/DZAnomalyFootStepSoundComponent.h"


//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━		

UDZAnomalyFootStepSoundComponent::UDZAnomalyFootStepSoundComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	

void UDZAnomalyFootStepSoundComponent::PlayFootstepSound(const FVector& Location, const bool bIsLeft)
{
	Super::PlayFootstepSound(Location, bIsLeft);
}

void UDZAnomalyFootStepSoundComponent::OnLanded(const FHitResult& Hit)
{
	Super::OnLanded(Hit);
}

#pragma endregion
//======================================================================================================================	
