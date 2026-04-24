// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/OriginActor/Door/DZOriginDoor.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━

void ADZOriginDoor::OnRep_IsOpened()
{
	if (bIsOpened) DoorTimeline->Play();
	else DoorTimeline->Reverse();
	
}

void ADZOriginDoor::OnRep_DoorSoundVarForRep()
{
	if (IsValid(DoorSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, DoorSound, GetActorLocation());
	}
}

#pragma endregion
//======================================================================================================================
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

ADZOriginDoor::ADZOriginDoor()
{
	// tick
	PrimaryActorTick.bCanEverTick = true;
	
	// network
	bReplicates = true; 

	// 문 메쉬
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

	// 타임라인
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

	// 기본 값 
	bIsOpened = false;
	ClosedRotation = FRotator::ZeroRotator;
	OpenedRotation = FRotator(0.f, 90.f, 0.f); 
	
	// ui
	InteractWidgetComp = CreateDefaultSubobject<UWidgetComponent>(FName("InteractWidgetComp"));
	InteractWidgetComp->SetupAttachment(GetRootComponent());
}


void ADZOriginDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZOriginDoor, bIsOpened);
	DOREPLIFETIME(ADZOriginDoor, DoorSoundVarForRep);
}

void ADZOriginDoor::BeginPlay()
{
	Super::BeginPlay();
	
	// 초기화
	if (!IsValid(DoorCurve)) return;
	
	// 타임라인 업데이트 함수 연결
	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("UpdateDoorRotation"));
	DoorTimeline->AddInterpFloat(DoorCurve, UpdateDelegate);
	
	// [추가] 초기 상태 동기화: 이미 열려 있는 상태로 스폰되었다면 끝 위치로 점프
	if (bIsOpened)
	{
		DoorTimeline->SetPlaybackPosition(DoorTimeline->GetTimelineLength(), false);
		UpdateDoorRotation(1.0f); // 문을 열린 상태로 즉시 회전
	}
}

#pragma endregion
//======================================================================================================================	
#pragma region DoorAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// DoorAPI
	//━━━━━━━━━━━━━━━━━━━━

void ADZOriginDoor::ToggleDoor(bool WantOpen)
{
	// onRep 호출 (클라 동기화)
	bIsOpened = WantOpen;
	++DoorSoundVarForRep;
	
	// 서버 로직 호출
	if (HasAuthority()) OnRep_IsOpened();
	if (HasAuthority()) OnRep_DoorSoundVarForRep();
	
	// 최초로 1회에 한정 (스테이지 넘어갈 때마다 리셋됨)
	if (bIsDoorForStartTimeHasBeenUsed == true) return;
		
	// 1회 사용 마크
	bIsDoorForStartTimeHasBeenUsed = true;
}

void ADZOriginDoor::UpdateDoorRotation(float Value)
{
	FRotator NewRotation = FMath::Lerp(ClosedRotation, OpenedRotation, Value);
	DoorMesh->SetRelativeRotation(NewRotation);
}

#pragma endregion
//======================================================================================================================
#pragma region 인터렉트_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_섹션
	//━━━━━━━━━━━━━━━━━━━━	

void ADZOriginDoor::ToggleInteractWidget_Implementation(bool InWantOn)
{
	// 위젯 컴포넌트 및 위젯 체크
	if (!IsValid(InteractWidgetComp)) return;
	if (!IsValid(InteractWidgetComp->GetUserWidgetObject())) return;
	
	// 켜고 끄기
	if (InWantOn == true) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	else if (InWantOn == false) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Collapsed);
}

void ADZOriginDoor::DoStandAloneInteractLogic_Implementation(FDZInteractData& InteractData)
{
	if (bIsOpened == true ) ToggleDoor(false);
	else if (bIsOpened == false) ToggleDoor(true);
}
#pragma endregion
//======================================================================================================================
