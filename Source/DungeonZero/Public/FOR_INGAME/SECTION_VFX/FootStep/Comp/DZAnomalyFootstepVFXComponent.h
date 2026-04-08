// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_VFX/FootStep/A_Base/DZFootStepVFXMasterComponent.h"
#include "DZAnomalyFootstepVFXComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZAnomalyFootstepVFXComponent : public UDZFootStepVFXMasterComponent
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	
	UDZAnomalyFootstepVFXComponent();

#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	
public:
	virtual void PlayFootstepVFX(const FVector& SocketLocation, const FRotator& CharacterRotation, bool& bIsLeft) override;
	virtual void OnLandedVFX(const FHitResult& Hit) override;
	
#pragma endregion
//======================================================================================================================		
};
