// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZDoorActor.h"
#include "Components/TimelineComponent.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
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
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true; 

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

	bIsOpened = false;
	ClosedRotation = FRotator::ZeroRotator;
	OpenedRotation = FRotator(0.f, 90.f, 0.f); 
}


void ADZDoorActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZDoorActor, bIsOpened);
}

void ADZDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (DoorCurve)
	{
		// 타임라인 업데이트 함수 연결
		FOnTimelineFloat UpdateDelegate;
		UpdateDelegate.BindUFunction(this, FName("UpdateDoorRotation"));
		DoorTimeline->AddInterpFloat(DoorCurve, UpdateDelegate);
	}
	
	// 문 열고 닫기 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	DoorToggleMessageHandle = MessageSubsystem.RegisterListener<FDZDoorMSG>(DZ::Stage::DZ_STAGE_OPENDOOR, this, &ADZDoorActor::OnDoorToggleMessageReceived);
	
}

void ADZDoorActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 메시지 시스템 구독 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(DoorToggleMessageHandle);
	}
	Super::EndPlay(EndPlayReason);
}
#pragma endregion
//======================================================================================================================	
#pragma region DoorAPI	

void ADZDoorActor::ToggleDoor(bool WantOpen)
{
	bIsOpened = WantOpen;
	if (HasAuthority()) OnRep_IsOpened();
}

void ADZDoorActor::UpdateDoorRotation(float Value)
{
	FRotator NewRotation = FMath::Lerp(ClosedRotation, OpenedRotation, Value);
	DoorMesh->SetRelativeRotation(NewRotation);
}

void ADZDoorActor::OnDoorToggleMessageReceived(FGameplayTag Channel, const FDZDoorMSG& Payload)
{
	// 자신이 속한 레벨과 메시지의 로드 레벨이 같을 때만 동작
	if (DoorLevel == Payload.StageLevel)
	{
		// bIsOpened가 메시지의 원하는 상태(bShouldOpen)와 다를 때만 토글
		if (bIsOpened != Payload.bIsDoorOpen) ToggleDoor(Payload.bIsDoorOpen);
		UE_LOG(LogTemp, Log, TEXT("%s: 내 레벨과 일치하여 문을 %s합니다."), *GetName(), Payload.bIsDoorOpen ? TEXT("엽니다") : TEXT("닫습니다"));
	}
}

#pragma endregion
//======================================================================================================================	