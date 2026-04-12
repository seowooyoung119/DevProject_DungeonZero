// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyPlayLoopSound.generated.h"

UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyPlayLoopSound : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZGCN_AnomalyPlayLoopSound();
	
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

#pragma endregion
//======================================================================================================================	
#pragma region 컴포넌트
	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트
	//━━━━━━━━━━━━━━━━━━━━	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent> AudioComponent;

#pragma endregion
//======================================================================================================================	
#pragma region 설정
	//━━━━━━━━━━━━━━━━━━━━
	// 설정
	//━━━━━━━━━━━━━━━━━━━━	
	void SpawnAndAttachSound_internal(AActor* MyTarget);
	
	// 재생할 루프 사운드 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> LoopSound;

#pragma endregion
//======================================================================================================================	
};
