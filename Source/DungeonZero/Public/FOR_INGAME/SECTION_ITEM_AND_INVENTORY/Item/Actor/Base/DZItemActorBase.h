// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZOriginMSG.h"
#include "GameFramework/Actor.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"
#include "FOR_INGAME/SECTION_INTERACT/Interface/DZCommonInteractInterface.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZItemRuntimeData.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Interface/DZItemInterface.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZItemActorBase.generated.h"

class UWidgetComponent;

UCLASS(NotBlueprintable, Abstract)
class DUNGEONZERO_API ADZItemActorBase : public AActor, public IDZCommonPlayRoleInterface, public IDZCommonInteractInterface, public IDZItemInterface
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	UFUNCTION()
	virtual void OnRep_ItemData();
	
	UFUNCTION()
	virtual void OnRep_bIsPickUpAble();
	
	UFUNCTION()
	virtual void OnRep_IsVisible();
	
	
	UFUNCTION()
	virtual void OnRep_bCanCollisionAble();
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZItemActorBase();
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 인터렉트_그리고_플레이롤_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_그리고_플레이롤_섹션
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// IDZCommonInteractInterface, IDZCommonPlayRoleInterface ~ 
	virtual void ToggleInteractWidget_Implementation(bool InWantOn) override;
	FORCEINLINE virtual EDZPlayRole GetPlayRole_Implementation() override { return PlayRole;}
	// ~ IDZCommonInteractInterface, IDZCommonPlayRoleInterface
	
protected:
	// 인터렉트 위젯 초기화 함수 (자식들이 호출할 것)
	virtual void InitInteractUI_internal(FDZItemRuntimeData& ItemRuntimeData);
	
	// 위젯 컴포넌트 선언 (자식들이 만들 것)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Item")
	TObjectPtr<UWidgetComponent> InteractWidgetComp = nullptr;
	
	// 롤 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Item")
	EDZPlayRole PlayRole = EDZPlayRole::Item;
	
#pragma endregion
//======================================================================================================================
#pragma region 아이템_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 아이템_API_및_데이터
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// IDZItemInterface ~ 
	FORCEINLINE virtual FDZItemRuntimeData& GetItemRuntimeDataPtr() override { return ItemData;};
	FORCEINLINE virtual void SetItemRuntimeData(FDZItemRuntimeData& InItemRuntimeData) override { ItemData = InItemRuntimeData;};
	/// ~ IDZItemInterface
	
	
protected:
	// 아이템 ID에 따른 초기화 함수 (자식들이 호출할것)
	virtual void InitItemID_Internal();
	
	// 아이템 데이터 
	UPROPERTY(ReplicatedUsing = OnRep_ItemData,VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Item")
	FDZItemRuntimeData ItemData;
	
	// 아이템 ID (레벨 배치시 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Item")
	int32 ItemIDIfLayOnLevel;
	
#pragma endregion
//======================================================================================================================
#pragma region 피직스_콜리전
	
public:
	// 자식들이 상속해서 코드 채울 것 
	virtual void SetTogglePhysicsAndCollisions(bool InWantOn);
	
protected:
	
	// 피직스 콜리전 토글
	UPROPERTY(ReplicatedUsing = OnRep_bIsPickUpAble,  meta=(RepNotifyMode = "Always"), EditAnywhere, BlueprintReadWrite, Category = "DZ | Item")
	bool bIsNotPickItem = true;
	
	// 비긴 플레이에서 피직스 켤거임?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Item")
	bool bWantOnPhysicsInBeginPlay = true;
	
#pragma endregion
//======================================================================================================================
#pragma region 게임_플레이_메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임_플레이_메시지 (레벨 배치 관련 )
	//━━━━━━━━━━━━━━━━━━━━	

protected:
	
	// 보이기, 숨김기 처리
	void OnOriginVisibleReceived(FGameplayTag Channel, const FDZOriginMSG& Payload);

	// IDZCommonInteractInterface, IDZCommonPlayRoleInterface ~ 
	virtual void ToggleHiddenInGame_Implementation(bool InIsVisible, bool InbCanCollisionAble) override;
	// ~ IDZCommonInteractInterface, IDZCommonPlayRoleInterface
	
	// 핸들 
	FGameplayMessageListenerHandle OriginVisibleListenerHandle;
	
	// 레벨에 배치되어 있는가? 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "DZ")
	bool bIsLayOnLevel = false;

	// 보이기 숨기기 
	UPROPERTY(ReplicatedUsing = OnRep_IsVisible,  meta=(RepNotifyMode = "Always"),EditAnywhere, BlueprintReadWrite, Category = "DZ")
	bool IsVisible = true;
	
	// 보이기 숨기기 
	UPROPERTY(ReplicatedUsing = OnRep_bCanCollisionAble, meta=(RepNotifyMode = "Always"), EditAnywhere, BlueprintReadWrite, Category = "DZ")
	bool bCanCollisionAble = true;
	
#pragma endregion
//======================================================================================================================		
	
	
	
};
