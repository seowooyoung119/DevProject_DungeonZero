// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZDoorActor.h"
#include "Components/TimelineComponent.h"
#include "FOR_COMMON/SECTION_LOG/Stage/Door/DZDoorLOG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================
#pragma region onRep
void ADZDoorActor::OnRep_IsOpened()
{
	if (bIsOpened) DoorTimeline->Play();
	else DoorTimeline->Reverse();
}

#pragma endregion
//======================================================================================================================
#pragma region LifeCycle

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
}


void ADZDoorActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZDoorActor, bIsOpened);
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

void ADZDoorActor::ToggleDoor(bool WantOpen)
{
	bIsOpened = WantOpen;
	if (HasAuthority()) OnRep_IsOpened();
}

void ADZDoorActor::OnDoorResetReceived(FGameplayTag Channel, const FDZDoorMSG& Payload)
{
	ToggleDoor(false);
}

void ADZDoorActor::UpdateDoorRotation(float Value)
{
	FRotator NewRotation = FMath::Lerp(ClosedRotation, OpenedRotation, Value);
	DoorMesh->SetRelativeRotation(NewRotation);
}

#pragma endregion
//======================================================================================================================
