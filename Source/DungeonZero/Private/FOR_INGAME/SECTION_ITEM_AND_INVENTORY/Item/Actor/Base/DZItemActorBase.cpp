// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZITemStaticData.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Item/DZDropItemGarbageCollectorSystem.h"
#include "FOR_INGAME/SECTION_STAGE/System/Item/DZRegisterLevelPlacedItemHelperSystem.h"
#include "FOR_INGAME/SECTION_UI/Interact/Item/DZItemInteractToggleUI.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/GameNetworkManager.h"
#include "Net/UnrealNetwork.h"


//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━
	
void ADZItemActorBase::OnRep_ItemData()
{
	// 미정
}

void ADZItemActorBase::OnRep_bIsPickUpAble()
{
	// 자식이 오버라이드
}

void ADZItemActorBase::OnRep_IsVisible()
{
	if (IsVisible) SetActorHiddenInGame(false);
	else SetActorHiddenInGame(true);
	
	if (IsValid(InteractWidgetComp)) InteractWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADZItemActorBase::OnRep_bCanCollisionAble()
{
	if (bCanCollisionAble) SetActorEnableCollision(true);
	else SetActorEnableCollision(false);
	
	if (IsValid(InteractWidgetComp)) InteractWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZItemActorBase::ADZItemActorBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// network
	bReplicates = true;
	SetReplicatingMovement(true);
	
}

bool ADZItemActorBase::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const
{
	if (bAlwaysRelevant || IsOwnedBy(ViewTarget) || IsOwnedBy(RealViewer) || this == ViewTarget || ViewTarget == GetInstigator())
	{
		return true;
	}
	else if (bNetUseOwnerRelevancy && Owner)
	{
		return Owner->IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}
	else if (bOnlyRelevantToOwner)
	{
		return false;
	}
	else if (RootComponent && RootComponent->GetAttachParent() && RootComponent->GetAttachParent()->GetOwner() && (Cast<USkeletalMeshComponent>(RootComponent->GetAttachParent()) || (RootComponent->GetAttachParent()->GetOwner() == Owner)))
	{
		return RootComponent->GetAttachParent()->GetOwner()->IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
	}

	// 제거 목록  : 히든 및 콜리전 관련 체크 코드 
	// 사유 : 게임 로직 상 히든과 콜리전을 꺼도 복제가 되어야 함
	
	if (!RootComponent)
	{
		UE_LOG(LogNet, Warning, TEXT("Actor %s / %s has no root component in AActor::IsNetRelevantFor. (Make bAlwaysRelevant=true?)"), *GetClass()->GetName(), *GetName() );
		return false;
	}

	return !GetDefault<AGameNetworkManager>()->bUseDistanceBasedRelevancy || IsWithinNetRelevancyDistance(SrcLocation);
}

void ADZItemActorBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// 아이템 데이터 
	DOREPLIFETIME(ADZItemActorBase, ItemData);
	DOREPLIFETIME(ADZItemActorBase, IsVisible);  
	DOREPLIFETIME(ADZItemActorBase, bCanCollisionAble); 
	DOREPLIFETIME(ADZItemActorBase, bIsNotPickItem);  
}

void ADZItemActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (bIsLayOnLevel == true)
	{
		// 레벨 배치 아이템 액터 등록
		UDZRegisterLevelPlacedItemHelperSystem* RegisterLevelPlacedItemHelperSystem = UDZRegisterLevelPlacedItemHelperSystem::Get(this);
		if (IsValid(RegisterLevelPlacedItemHelperSystem)) RegisterLevelPlacedItemHelperSystem->RegisterLevelPlacedItem(this);
	
		// 레벨 배치 아이템 핸들 시스템 메시지 구독 (현재 원본 액터와 같이 함)
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		OriginVisibleListenerHandle = MessageSubsystem.RegisterListener<FDZOriginMSG>(DZ::OriginMSG::DZ_ORIGIN_VISIBILE_NOTICE, this, &ADZItemActorBase::OnOriginVisibleReceived);
	}
	else
	{
		// 드랍 아이템 가비지 컬렉터 구독
		UDZDropItemGarbageCollectorSystem* DropItemGarbageCollectorSystem = UDZDropItemGarbageCollectorSystem::Get(this);
		if (IsValid(DropItemGarbageCollectorSystem)) DropItemGarbageCollectorSystem->RegisterDropItem(this);
	}
}

void ADZItemActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		if (OriginVisibleListenerHandle.IsValid()) MessageSubsystem.UnregisterListener(OriginVisibleListenerHandle);
	}
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region 인터렉트API_컴포넌트_데이터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트API_컴포넌트_데이터
	//━━━━━━━━━━━━━━━━━━━━	

void ADZItemActorBase::InitInteractUI_internal(FDZItemRuntimeData& ItemRuntimeData)
{
	// 윚세 컴포넌트 및 위젯 체크
	if (!IsValid(InteractWidgetComp)) return;
	if (!IsValid(InteractWidgetComp->GetUserWidgetObject())) return;
	UDZItemInteractToggleUI* InteractUI = CastChecked<UDZItemInteractToggleUI>(InteractWidgetComp->GetUserWidgetObject());
	if (!IsValid(InteractUI)) return;
	
	// 정적 데이터 가져오기 
	if (!IsValid(GetWorld())) return;
	UDZItemDataSubSystem* DataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(DataSubSystem)) return;
	FDZITemStaticData* ItemStaticData = DataSubSystem->GetItemStaticData(ItemRuntimeData.StaticDataID);
	if (!ItemStaticData) return;

	// 상호작용 키, 이름 넘겨주기
	FText InteractKeyText = ItemStaticData->ItemStaticInfo.ItemInteractKeyType;
	InteractUI->InitInteractInfo(ItemStaticData->ItemStaticInfo.ItemName, InteractKeyText);
	
	// 설정 후 숨기기 (기본값)
	InteractUI->SetVisibility(ESlateVisibility::Collapsed);
}

void ADZItemActorBase::ToggleInteractWidget_Implementation(bool InWantOn)
{
	// 위젯 컴포넌트 및 위젯 체크
	if (!IsValid(InteractWidgetComp)) return;
	if (!IsValid(InteractWidgetComp->GetUserWidgetObject())) return;
	
	// 켜고 끄기
	if (InWantOn == true) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	else if (InWantOn == false) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Collapsed);
}

#pragma endregion
//======================================================================================================================
#pragma region 아이템_섹션

void ADZItemActorBase::InitItemID_Internal()
{
	// 정적 데이터 가져오기
	UDZItemDataSubSystem* DataSubSystem = UDZItemDataSubSystem::Get(GetWorld());
	if (!IsValid(DataSubSystem)) return;
	FDZITemStaticData* ItemStaticData = DataSubSystem->GetItemStaticData(ItemIDIfLayOnLevel);
	if (!ItemStaticData) return;
	
	// 새 데이터 만들기
	FDZItemRuntimeData NewItemRuntimeData;
	NewItemRuntimeData.DynamicData.CurrentStack = 1;
	NewItemRuntimeData.StaticDataID = ItemIDIfLayOnLevel;
	
	// 데이터 주입
	ItemData = NewItemRuntimeData;
}

#pragma endregion
//======================================================================================================================
#pragma region 피직스_콜리전

void ADZItemActorBase::SetTogglePhysicsAndCollisions(bool InWantOn)
{
}

#pragma endregion
//======================================================================================================================	
#pragma region 게임_플레이_메시지
	
//━━━━━━━━━━━━━━━━━━━━
// 플레이롤
//━━━━━━━━━━━━━━━━━━━━	

void ADZItemActorBase::OnOriginVisibleReceived(FGameplayTag Channel, const FDZOriginMSG& Payload)
{
	Execute_ToggleHiddenInGame(this, Payload.bIsVisible, Payload.bIsVisible);
}

void ADZItemActorBase::ToggleHiddenInGame_Implementation(bool InIsVisible, bool InbCanCollisionAble)
{
	if (InIsVisible) SetActorHiddenInGame(false);
	else SetActorHiddenInGame(true);

	if (InbCanCollisionAble) SetActorEnableCollision(true);
	else SetActorEnableCollision(false);
		
	if (IsValid(InteractWidgetComp)) InteractWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
	IsVisible = InIsVisible;
	bCanCollisionAble = InbCanCollisionAble;
}

#pragma endregion
//======================================================================================================================		
	
	