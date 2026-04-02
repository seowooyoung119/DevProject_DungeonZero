// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"
#include "DZAnomalyActorBase.generated.h"

class UDZGiveGAGEDataAsset;
class UAbilitySystemComponent;

UCLASS()
class DUNGEONZERO_API ADZAnomalyActorBase : public AActor, public IAbilitySystemInterface, public IDZCommonPlayRoleInterface
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

public:
	ADZAnomalyActorBase();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion
//======================================================================================================================		
#pragma region 플레이롤
	
	//━━━━━━━━━━━━━━━━━━━━
	// 플레이롤
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// IDZCommonPlayRoleInterface ~ 
	FORCEINLINE virtual EDZPlayRole GetPlayRole_Implementation() override { return PlayRole;}
	// ~ IDZCommonInteractInterface
	
protected:
	// 롤 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | AnomalyActor | PlayRole")
	EDZPlayRole PlayRole = EDZPlayRole::Anomaly;
#pragma endregion
//======================================================================================================================		

	#pragma region 어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리
	//━━━━━━━━━━━━━━━━━━━━	

public:
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AnomalyAbilitySystemComponent;
	};
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	void SetAnomalyScale(float InScale);

protected:
	// 어빌리티 랜덤 선택 및 부여
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC);
	// 어빌리티 실행
	virtual void ActivateAnomaly_internal(UAbilitySystemComponent* InASC);
	// 스케일 변경 복제
	UFUNCTION()
	void OnRep_AnomalyScale();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | AnomalyActor")
	TObjectPtr<UAbilitySystemComponent> AnomalyAbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " DZ | AnomalyActor")
	TObjectPtr<UDZGiveGAGEDataAsset> BaseGAGEData = nullptr;

	// 부여된 어빌리티 핸들 저장
	UPROPERTY()
	FGameplayAbilitySpecHandle AnomalyAbilitySpecHandle;
	// 어노말리 스케일
	UPROPERTY(ReplicatedUsing = OnRep_AnomalyScale)
	float ReplicatedAnomalyScale = 1.0f;

#pragma endregion
//======================================================================================================================		
};