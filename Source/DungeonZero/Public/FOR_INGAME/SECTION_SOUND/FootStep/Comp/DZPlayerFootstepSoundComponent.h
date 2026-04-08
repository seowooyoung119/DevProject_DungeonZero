// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_SOUND/FootStep/A_Base/DZFootStepSoundMasterComponent.h"
#include "DZPlayerFootstepSoundComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZPlayerFootstepSoundComponent : public UDZFootStepSoundMasterComponent
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━		
	
public:
	UDZPlayerFootstepSoundComponent();

#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// 걷기, 달리기 소리
	virtual void PlayFootstepSound(const FVector& Location, const bool bIsLeft = true) override;

	// 착지할 때 소리
	virtual void OnLanded(const FHitResult& Hit) override;
	
#pragma endregion
//======================================================================================================================	
};
