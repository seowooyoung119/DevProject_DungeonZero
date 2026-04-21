// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"
#include "FOR_INGAME/SECTION_ANOMALY/Interface/DZAnomalyIsFakeInterface.h"
#include "FOR_INGAME/SECTION_ANOMALY/Interface/DZAnomalySealAdditionalFunction.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZAnomalyGrantData.h"
#include "FOR_INGAME/SECTION_STAGE/Data/Struct/DZFakeAnomalySeeInfo.h"
#include "DZAnomalyActorBase.generated.h"

struct FDZFakeAnomalySeeInfo;
class UDZAnomalyGrantDataAsset;
class UAbilitySystemComponent;

UCLASS()
class DUNGEONZERO_API ADZAnomalyActorBase : public AActor, public IAbilitySystemInterface,
                                            public IDZCommonPlayRoleInterface,
                                            public IDZAnomalySealAdditionalFunction, public IDZAnomalyIsFakeInterface
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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion
//======================================================================================================================
#pragma region 게터/세터

	//━━━━━━━━━━━━━━━━━━━━
	// 게터/세터
	//━━━━━━━━━━━━━━━━━━━━	
public:
	virtual UPrimitiveComponent* GetAnomalyPrimitiveComponent() { return nullptr; }
	void SetFakeAnomalySeeInfo(const FDZFakeAnomalySeeInfo& InInfo);

#pragma endregion
//======================================================================================================================
#pragma region 컴포넌트

	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트
	//━━━━━━━━━━━━━━━━━━━━	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | AnomalyActor")
	TObjectPtr<UAbilitySystemComponent> AnomalyAbilitySystemComponent = nullptr;
#pragma endregion
//======================================================================================================================		
#pragma region 플레이롤

	//━━━━━━━━━━━━━━━━━━━━
	// 플레이롤
	//━━━━━━━━━━━━━━━━━━━━	

public:
	// IDZCommonPlayRoleInterface ~ 
	FORCEINLINE virtual EDZPlayRole GetPlayRole_Implementation() override { return PlayRole; }
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

protected:
	// 어빌리티 랜덤 선택 및 부여
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC);
	// 어빌리티 실행
	virtual void ActivateAnomaly_internal(UAbilitySystemComponent* InASC);

	// 부여할 어빌리티 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = " DZ | AnomalyActor")
	TSubclassOf<UGameplayAbility> AnomalyGameplayAbility;
	// 오버랩시 활성화
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | AnomalyActor")
	bool bActivateOnTrigger = true;
	// 오버랩 종료시 비활성화
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | AnomalyActor")
	bool bDeactivateOnTrigger = true;
	
	// 부여된 어빌리티 핸들 저장
	UPROPERTY()
	FGameplayAbilitySpecHandle AnomalyAbilitySpecHandle;

#pragma endregion
//======================================================================================================================
#pragma region 어노말리_엔딩_펑션

	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리 엔딩 펑션
	//━━━━━━━━━━━━━━━━━━━━	
public:
	// GAS로 하기 비효율적이거나 액터와 연관이 되어 있을 경우 이 인터페이스의 API를 상속하여 로직을 추가한 뒤 GAS의 EndAbility 에서 인터페이스 호출 
	virtual void AnomalySealAdditionalFunction_Implementation() override { return; };

#pragma endregion
//======================================================================================================================	
#pragma region 가짜_어노말리

	//━━━━━━━━━━━━━━━━━━━━
	// 가짜_어노말리
	//━━━━━━━━━━━━━━━━━━━━	
public:
	virtual bool IsFakeAnomaly() const override { return FakeAnomalySeeInfo.CanSeePlayers.Num() > 0; }
private:
	// 가짜 어노말리를 볼 수 있는 플레이어 캐릭터 목록
	UPROPERTY(ReplicatedUsing=OnRep_FakeAnomalySeeInfo)
	FDZFakeAnomalySeeInfo FakeAnomalySeeInfo;
	UFUNCTION()
	void OnRep_FakeAnomalySeeInfo();

#pragma endregion
//======================================================================================================================	
};
