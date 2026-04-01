// All CopyRight From YulRyongGameStudio //

#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/SkeletalMeshItem/DZSkeletalMeshItem.h"
#include "Components/WidgetComponent.h"

//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━

void ADZSkeletalMeshItem::OnRep_bIsPickUpAble()
{
	SetTogglePhysicsAndCollisions(bIsNotPickItem);
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZSkeletalMeshItem::ADZSkeletalMeshItem()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// 스켈레탈 메쉬
	ItemSkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMeshComp"));
	SetRootComponent(ItemSkeletalMeshComp);
	
	// 위젯 컴포넌트 
	InteractWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComp"));
	InteractWidgetComp->SetupAttachment(GetRootComponent());
	InteractWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void ADZSkeletalMeshItem::BeginPlay()
{
	Super::BeginPlay();
	
	// 서버에서 피직스 실행
	if (HasAuthority() && bWantOnPhysicsInBeginPlay) ItemSkeletalMeshComp->SetSimulatePhysics(true);
	
	// 데이터 주입 
	InitItemID_Internal();

	// 위젯 컴포넌트 초기화 
	InitInteractUI_internal(ItemData);
}

	
#pragma endregion
//======================================================================================================================
#pragma region 피직스_콜리전
	
void ADZSkeletalMeshItem::SetTogglePhysicsAndCollisions(bool InWantOn)
{
	bIsNotPickItem = InWantOn;
	ItemSkeletalMeshComp->SetCollisionEnabled(InWantOn ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
}

#pragma endregion
//======================================================================================================================