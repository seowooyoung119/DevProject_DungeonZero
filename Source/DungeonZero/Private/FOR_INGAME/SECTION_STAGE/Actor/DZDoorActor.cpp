// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZDoorActor.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/Control/DZStageControlSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━

void ADZDoorActor::OnRep_IsOpened()
{
	if (bIsOpened) DoorTimeline->Play();
	else DoorTimeline->Reverse();
	
}

void ADZDoorActor::OnRep_DoorSoundVarForRep()
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

ADZDoorActor::ADZDoorActor()
{
	// tick
	PrimaryActorTick.bCanEverTick = true;
	
	// network
	bReplicates = true; 

	// 문 메쉬
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

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


void ADZDoorActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZDoorActor, bIsOpened);
	DOREPLIFETIME(ADZDoorActor, DoorSoundVarForRep);
}

void ADZDoorActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 메시지 구독 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(TimeResetListenerHandle);
	}
	Super::EndPlay(EndPlayReason);
}

void ADZDoorActor::BeginPlay()
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
	
	// 리셋 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	TimeResetListenerHandle = MessageSubsystem.RegisterListener<FDZDoorMSG>(DZ::DoorMSG::DZ_DOOR_DOORRESET, this, &ADZDoorActor::OnDoorResetReceived);
}

#pragma endregion
//======================================================================================================================	
#pragma region DoorAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// DoorAPI
	//━━━━━━━━━━━━━━━━━━━━

void ADZDoorActor::ToggleDoor(bool WantOpen)
{
	// onRep 호출 (클라 동기화)
	bIsOpened = WantOpen;
	++DoorSoundVarForRep;
	
	// 서버 로직 호출
	if (HasAuthority()) OnRep_IsOpened();
	if (HasAuthority()) OnRep_DoorSoundVarForRep();
	
	// 최초로 1회에 한정 (스테이지 넘어갈 때마다 리셋됨)
	if (bIsDoorForStartTimeHasBeenUsed == true) return;
	
	// 타이머 시작 요청
	UDZStageControlSystem* StageControlSystem = UDZStageControlSystem::Get(this);
	if (!IsValid(StageControlSystem)) return;
	StageControlSystem->AllowStartTimeTick();
	
	// 1회 사용 마크
	bIsDoorForStartTimeHasBeenUsed = true;
}

void ADZDoorActor::UpdateDoorRotation(float Value)
{
	FRotator NewRotation = FMath::Lerp(ClosedRotation, OpenedRotation, Value);
	DoorMesh->SetRelativeRotation(NewRotation);
}

#pragma endregion
//======================================================================================================================
#pragma region 게임플레이_메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임플레이_메시지
	//━━━━━━━━━━━━━━━━━━━━

void ADZDoorActor::OnDoorResetReceived(FGameplayTag Channel, const FDZDoorMSG& Payload)
{
	// onRep 호출 (클라 동기화)
	bIsOpened = Payload.bIsDoorOpen;
	
	// 서버 로직 호출 (사운드 제외)
	if (HasAuthority()) OnRep_IsOpened();
	
	// 1회 사용 마크 리셋
	bIsDoorForStartTimeHasBeenUsed = false;
}


#pragma endregion
//======================================================================================================================
#pragma region 인터렉트_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_섹션
	//━━━━━━━━━━━━━━━━━━━━	

void ADZDoorActor::ToggleInteractWidget_Implementation(bool InWantOn)
{
	// 위젯 컴포넌트 및 위젯 체크
	if (!IsValid(InteractWidgetComp)) return;
	if (!IsValid(InteractWidgetComp->GetUserWidgetObject())) return;
	
	// 켜고 끄기
	if (InWantOn == true) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
	else if (InWantOn == false) InteractWidgetComp->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Collapsed);
}

void ADZDoorActor::DoStandAloneInteractLogic_Implementation(FDZInteractData& InteractData)
{
	if (bIsOpened == true ) ToggleDoor(false);
	else if (bIsOpened == false) ToggleDoor(true);
}
#pragma endregion
//======================================================================================================================