// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/FootStep/Comp/DZPlayerFootstepSoundComponent.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━		

UDZPlayerFootstepSoundComponent::UDZPlayerFootstepSoundComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	

void UDZPlayerFootstepSoundComponent::PlayFootstepSound(const FVector& Location, const bool bIsLeft)
{
	Super::PlayFootstepSound(Location, bIsLeft);
}

void UDZPlayerFootstepSoundComponent::OnLanded(const FHitResult& Hit)
{
	Super::OnLanded(Hit);
}

#pragma endregion
//======================================================================================================================	
