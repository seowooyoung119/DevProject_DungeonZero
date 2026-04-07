// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_PLAYER/Controller/DZPlayerController.h"

#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAllowPlayerControlMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━

void ADZPlayerController::OnRep_IsVisibleAndMovable()
{
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	FDZAllowPlayerControlMSG Payload;
	Payload.CanMoveAndSee = IsVisibleAndMovable;
	MessageSubsystem.BroadcastMessage(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, Payload);
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
ADZPlayerController::ADZPlayerController()
{
	// tick
	PrimaryActorTick.bCanEverTick = true;
}

void ADZPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(ADZPlayerController, IsVisibleAndMovable, COND_OwnerOnly);
}

void ADZPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// 카메라 페이드
	if (IsValid(PlayerCameraManager)) PlayerCameraManager->StartCameraFade(1.f, 0.f, 10.f, FLinearColor::Black, 
		true, true);
	
	// 입력 모드 설정
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	bShowMouseCursor = false;
	
	// 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	CanMoveAndSeeListenerHandle = MessageSubsystem.RegisterListener<FDZAllowPlayerControlMSG>(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, this, &ADZPlayerController::OnCanMoveAndSeeReceived);
}

void ADZPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(CanMoveAndSeeListenerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	
	
//━━━━━━━━━━━━━━━━━━━━
// StageAPI
//━━━━━━━━━━━━━━━━━━━━

void ADZPlayerController::OnCanMoveAndSeeReceived(FGameplayTag Channel, const FDZAllowPlayerControlMSG& Payload)
{
	if (Payload.CanMoveAndSee == true)
	{
		FInputModeGameOnly GameOnlyInputMode;
		SetInputMode(GameOnlyInputMode);
		if (IsValid(PlayerCameraManager)) PlayerCameraManager->StartCameraFade(1.f, 0.f, 3.f, FLinearColor::Black, 
			true);
		IsVisibleAndMovable = true;
	}
	else
	{
		FInputModeUIOnly UIOnlyInputMode;
		SetInputMode(UIOnlyInputMode);
		if (IsValid(PlayerCameraManager))  PlayerCameraManager->StartCameraFade(0.f, 1.f, 3.f, FLinearColor::Black,
			true, true);
		IsVisibleAndMovable = false;
	}
}

#pragma endregion
//======================================================================================================================	