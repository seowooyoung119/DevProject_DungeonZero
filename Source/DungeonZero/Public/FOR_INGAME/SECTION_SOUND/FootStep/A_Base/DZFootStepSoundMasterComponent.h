// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DZFootStepSoundMasterComponent.generated.h"


class UDZFootStepSoundDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZFootStepSoundMasterComponent : public UActorComponent
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	
	UDZFootStepSoundMasterComponent();
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// 걷기, 달리기 소리
	UFUNCTION(BlueprintCallable, Category = "DZ | Footstep")
	virtual void PlayFootstepSound(const FVector& Location, const bool bIsLeft = true);

	// 착지할 때 소리
	UFUNCTION(BlueprintCallable, Category = "DZ | Footstep")
	virtual void OnLanded(const FHitResult& Hit);
	
protected:
	
	// 사운드 데이터 에셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Footstep")
	TObjectPtr<UDZFootStepSoundDataAsset> FootStepSoundDataAsset = nullptr;
	
	// 오너 캐릭터 캐싱 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Footstep")
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
