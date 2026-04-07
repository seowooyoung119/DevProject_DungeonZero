// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_UI/A_InGameOverlay/DZInGameOverlay.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
	
void UDZInGameOverlay::NativeConstruct()
{
	Super::NativeConstruct();

	// 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	CanMoveAndSeeListenerHandle = MessageSubsystem.RegisterListener<FDZAllowPlayerControlMSG>(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, this, &UDZInGameOverlay::OnCanMoveAndSeeReceived);

}

void UDZInGameOverlay::NativeDestruct()
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(CanMoveAndSeeListenerHandle);
	}
	
	Super::NativeDestruct();
}

#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━

void UDZInGameOverlay::OnCanMoveAndSeeReceived(FGameplayTag Channel, const FDZAllowPlayerControlMSG& Payload)
{
	StartFadeInAndOut(Payload.CanMoveAndSee);
}

#pragma endregion
//======================================================================================================================	