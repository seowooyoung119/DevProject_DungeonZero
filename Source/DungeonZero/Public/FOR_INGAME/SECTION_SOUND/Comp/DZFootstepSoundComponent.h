// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZSoundComponent.h"
#include "FOR_INGAME/SECTION_SOUND/Data/DZFootstepSoundData.h"
#include "DZFootstepSoundComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZFootstepSoundComponent : public UDZSoundComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDZFootstepSoundComponent();

protected:
	virtual void BeginPlay() override;

public:
	// 걷기, 달리기 소리
	UFUNCTION(BlueprintCallable, Category = "DZ | Footstep")
	void PlayFootstepSound(const FVector& Location, const bool bIsLeft = true);

	// 착지할 때 소리
	UFUNCTION(BlueprintCallable, Category = "DZ | Footstep")
	void OnLanded(const FHitResult& Hit);
	
protected:
	// 표면별 사운드
	UPROPERTY(EditDefaultsOnly, Category = "DZ | Footstep")
	TMap<TEnumAsByte<EPhysicalSurface>, FDZFootstepSoundData> FootstepSounds;

	// Default 사운드
	UPROPERTY(EditDefaultsOnly, Category = "DZ | Footstep")
	FDZFootstepSoundData DefaultFootstepSound;

	// 오너 캐릭터 캐싱 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Footstep")
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;
};
