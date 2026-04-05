// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "DZGCN_AnomalyEyeLight.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API ADZGCN_AnomalyEyeLight : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	ADZGCN_AnomalyEyeLight();
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 컴포넌트_및_데이터

	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트_및_데이터
	//━━━━━━━━━━━━━━━━━━━━	
protected:
	UPROPERTY(VisibleAnywhere, Category = "DZ")
	TObjectPtr<UStaticMeshComponent> Eye = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FName EyeLightTargetMeshTag = FName(TEXT(""));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FName AttachSocketName = FName(TEXT(""));
	
#pragma endregion
//======================================================================================================================		
};
