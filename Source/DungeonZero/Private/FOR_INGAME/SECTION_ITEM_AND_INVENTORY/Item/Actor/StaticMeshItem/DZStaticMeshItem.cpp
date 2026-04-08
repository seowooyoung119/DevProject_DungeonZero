// All CopyRight From YulRyongGameStudio //


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/StaticMeshItem/DZStaticMeshItem.h"
#include "Components/WidgetComponent.h"

//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━

void ADZStaticMeshItem::OnRep_bIsPickUpAble()
{
	SetTogglePhysicsAndCollisions(bIsNotPickItem);
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZStaticMeshItem::ADZStaticMeshItem()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// net
	bReplicates = true;
	SetReplicatingMovement(true);
	
	// 스태틱 메쉬
	ItemStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMeshComp"));
	SetRootComponent(ItemStaticMeshComp);	
	
	// 위젯 컴포넌트 
	InteractWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComp"));
	InteractWidgetComp->SetupAttachment(GetRootComponent(), FName("InteractUISocket"));
	InteractWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADZStaticMeshItem::BeginPlay()
{
	Super::BeginPlay();

	// 서버에서 피직스 실행
	if (HasAuthority() && bWantOnPhysicsInBeginPlay) ItemStaticMeshComp->SetSimulatePhysics(true);
	
	// 데이터 주입 
	InitItemID_Internal();
	
	// 위젯 컴포넌트 초기화 
	InitInteractUI_internal(ItemData);
}

#pragma endregion
//======================================================================================================================
#pragma region 피직스_콜리전
	
void ADZStaticMeshItem::SetTogglePhysicsAndCollisions(bool InWantOn)
{
	bIsNotPickItem = InWantOn;
	ItemStaticMeshComp->SetCollisionEnabled(InWantOn ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	if (HasAuthority()) ItemStaticMeshComp->SetSimulatePhysics(InWantOn);
}

#pragma endregion
//======================================================================================================================