// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FOR_INGAME/SECTION_VFX/FootStep/Data/Struct/DZFootStepVFXData.h"
#include "DZFootStepVFXMasterComponent.generated.h"


class UDZFootStepVFXDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZFootStepVFXMasterComponent : public UActorComponent
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	UDZFootStepVFXMasterComponent();
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	/** 발자국 VFX 및 데칼 생성 */
	UFUNCTION(BlueprintCallable, Category = "DZ | VFX")
	virtual void PlayFootstepVFX(const FVector& SocketLocation, const FRotator& SocketRotation, bool& bIsLeft);

	/** 착지 시 이펙트 (보통 양발 동시 혹은 더 큰 이펙트) */
	UFUNCTION(BlueprintCallable, Category = "DZ | VFX")
	virtual void OnLandedVFX(const FHitResult& Hit);

protected:
	// 실제 vfx 및 데칼 생성
	void SpawnVFXAndDecal(const FVector& SocketLocation, const FRotator& SocketRotation, const FDZFootstepVFXData& Data, const FHitResult& Hit, bool bIsLeft);

	// vfx 및 데칼 데이터 에셋
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | VFX")
	TObjectPtr<UDZFootStepVFXDataAsset> FootStepVfxDataAsset = nullptr;
	
	// 오너 캐릭터 캐싱 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Footstep")
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;
	
	// 생성된 발자국들
	UPROPERTY()
	TArray<TWeakObjectPtr<UDecalComponent>> FootPrints = {};
	
#pragma endregion
//======================================================================================================================		
};
