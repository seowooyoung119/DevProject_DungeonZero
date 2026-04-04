// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZOriginMSG.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZOriginActorBase.generated.h"

UCLASS()
class DUNGEONZERO_API ADZOriginActorBase : public AActor, public IDZCommonPlayRoleInterface
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region OnRep

	//━━━━━━━━━━━━━━━━━━━━
	// OnRep
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	UFUNCTION()
	FORCEINLINE void OnRepIsVisible()
	{
		if (IsVisible) SetActorHiddenInGame(false);
		else SetActorHiddenInGame(true);
	}
	
	UFUNCTION()
	FORCEINLINE void OnRepbCanCollisionAble()
	{
		if (bCanCollisionAble) SetActorEnableCollision(true);
		else SetActorEnableCollision(false);
	}
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

public:
	ADZOriginActorBase();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
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
	FORCEINLINE virtual void ToggleHiddenInGame_Implementation(bool InIsVisible, bool InbCanCollisionAble) override
	{
		if (InIsVisible) SetActorHiddenInGame(false);
		else SetActorHiddenInGame(true);
	
		if (InbCanCollisionAble) SetActorEnableCollision(true);
		else SetActorEnableCollision(false);

		IsVisible = InIsVisible;
		bCanCollisionAble = InbCanCollisionAble;
	}
	// ~ IDZCommonInteractInterface, IDZCommonPlayRoleInterface
	
protected:
	// 롤 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | OriginActor")
	EDZPlayRole PlayRole = EDZPlayRole::None;
	
#pragma endregion
//======================================================================================================================	
#pragma region 게임_플레이_메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 플레이롤
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// 보이기, 숨김기 처리
	void OnOriginVisibleReceived(FGameplayTag Channel, const FDZOriginMSG& Payload);

	// 핸들 
	FGameplayMessageListenerHandle OriginVisibleListenerHandle;
	
	// 보이기 숨기기 
	UPROPERTY(ReplicatedUsing = OnRepIsVisible, EditAnywhere, BlueprintReadWrite, Category = "DZ | OriginActor")
	bool IsVisible = true;
	
	// 보이기 숨기기 
	UPROPERTY(ReplicatedUsing = OnRepbCanCollisionAble, EditAnywhere, BlueprintReadWrite, Category = "DZ | OriginActor")
	bool bCanCollisionAble = true;
	
#pragma endregion
//======================================================================================================================	
};
