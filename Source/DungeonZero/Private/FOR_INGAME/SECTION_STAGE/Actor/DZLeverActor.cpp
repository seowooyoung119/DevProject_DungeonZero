// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZLeverActor.h"
#include "Components/WidgetComponent.h"
#include "FOR_INGAME/SECTION_STAGE/Actor/DZDoorActor.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZLeverActor::ADZLeverActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	LeverRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(LeverRoot);
		
	// ui
	InteractWidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("InteractWidgetComp"));
	InteractWidgetComp->SetupAttachment(GetRootComponent());
}

#pragma endregion
//======================================================================================================================	
#pragma region 인터렉트_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_섹션
	//━━━━━━━━━━━━━━━━━━━━	
	

void ADZLeverActor::ToggleInteractWidget_Implementation(bool InWantOn)
{
	// 위젯 컴포넌트 및 위젯 체크
	if (!IsValid(InteractWidgetComp)) return;
	if (!IsValid(InteractWidgetComp->GetUserWidgetObject())) return;
	
	// 켜고 끄기
	if (InWantOn == true) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	else if (InWantOn == false) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Collapsed);
}

void ADZLeverActor::DoStandAloneInteractLogic_Implementation(FDZInteractData& InteractData)
{
	if (!HasAuthority()) return;
	if (!IsValid(TargetDoor)) return;

	if (!TargetDoor->GetClass()->ImplementsInterface(UDZCommonInteractInterface::StaticClass())) return;
	IDZCommonInteractInterface::Execute_DoStandAloneInteractLogic(TargetDoor, InteractData);
}

#pragma endregion
//======================================================================================================================	