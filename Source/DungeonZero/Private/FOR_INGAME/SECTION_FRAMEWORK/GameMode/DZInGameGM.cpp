// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_FRAMEWORK/GameMode/DZInGameGM.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Dead/DZDeadTag.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_FRAMEWORK/GameState/DZInGameGameState.h"
#include "GameFramework/PlayerState.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

void ADZInGameGM::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	PlayerDeathListenerHandle = MessageSubsystem.RegisterListener(DZ::GameModeMSG::DZ_GAMEMODE_DEADCOUNT, this, &ADZInGameGM::OnPlayerDeathReceived);
	
}

void ADZInGameGM::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(PlayerDeathListenerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region 죽음_처리
	
	//━━━━━━━━━━━━━━━━━━━━
	// 죽음 처리
	//━━━━━━━━━━━━━━━━━━━━

void ADZInGameGM::OnPlayerDeathReceived(FGameplayTag Channel, const FDZGameModeDeathCountMSG& Payload)
{
	AGameStateBase* GameStateBase = GetGameState<AGameStateBase>();
	if (!IsValid(GameStateBase))
	{
		return;
	}
	
	for (auto& Player : GameStateBase->PlayerArray)
	{
		APawn* Pawn = Player->GetPawn();
		if (!IsValid(Pawn))
		{
			continue;
		}
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn);
		if (!IsValid(ASC))
		{
			continue;
		}
		
		if (ASC->HasMatchingGameplayTag(DZ::Dead::DZ_DEAD_PLAYER) == false)
		{
			return;
		}
	}
	
	GoToLobbyIfAllDead();
}

#pragma endregion
//======================================================================================================================	

	