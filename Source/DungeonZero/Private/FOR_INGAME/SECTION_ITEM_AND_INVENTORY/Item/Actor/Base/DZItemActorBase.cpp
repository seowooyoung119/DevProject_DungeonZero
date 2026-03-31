// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "Components/WidgetComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZITemStaticData.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/System/DZItemDataSubSystem.h"
#include "FOR_INGAME/SECTION_UI/Interact/Item/DZItemInteractToggleUI.h"
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

void ADZItemActorBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// 아이템 데이터 
	DOREPLIFETIME_CONDITION(ADZItemActorBase, ItemData, COND_None);
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
