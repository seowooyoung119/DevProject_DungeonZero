// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZSignBoard.h"
#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"
#include "Components/WidgetComponent.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_UI/Stage/SignBoard/DZSignBoardUI.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================	
#pragma region OnRep

	//━━━━━━━━━━━━━━━━━━━━
	// REP_API
	//━━━━━━━━━━━━━━━━━━━━

void ADZSignBoard::OnRep_CurrentLevel()
{
	UpdateUIbyCurrentLevel();
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

ADZSignBoard::ADZSignBoard()
{
	// tick 
	PrimaryActorTick.bCanEverTick = false;
	
	// network
	bReplicates = true;
	
	// 컴포넌트 구성
	SignBoardRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootScene"));
	SetRootComponent(SignBoardRoot);
	
	SignBoardWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SignBoardWidgetComponent"));
	SetRootComponent(GetRootComponent());
}

void ADZSignBoard::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZSignBoard, CurrentLevel);
}

void ADZSignBoard::BeginPlay()
{
	Super::BeginPlay();
	
	// 스테이지 런타임 데이터 모듈 체크
	UUDZStageRuntimePlayDataModule* StageRuntimePlayDataModule = UUDZStageRuntimePlayDataModule::Get(this);
	if (!IsValid(StageRuntimePlayDataModule)) return;
	
	// 스테이지 레벨 캐싱 및 업데이트
	UpdateUIbyCurrentLevel();
	CurrentLevel = StageRuntimePlayDataModule->GetCurrentLevel();
	
	// 타임 리셋, 타임 감소 구독, 타임 오버 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	CurrentLevelNoticeListenerHandle = MessageSubsystem.RegisterListener<FDZStageMSG>(DZ::StageMSG::DZ_STAGE_CURRENTLEVEL_NOTICE, this, &ADZSignBoard::OnCurrentLevelNoticeReceived);

	// 처음에 숨기기
	if (!IsValid(SignBoardWidgetComponent->GetWidget())) return;
	SignBoardWidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Hidden);
	
}

void ADZSignBoard::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(CurrentLevelNoticeListenerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region SignBoardAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// SignBoardAPI
	//━━━━━━━━━━━━━━━━━━━━

void ADZSignBoard::OnCurrentLevelNoticeReceived(FGameplayTag Channel, const FDZStageMSG& Payload)
{
	CurrentLevel = Payload.LoadStage;
	UpdateUIbyCurrentLevel();
}

void ADZSignBoard::UpdateUIbyCurrentLevel()
{
	if (!IsValid(SignBoardWidgetComponent)) return;
	
	UDZSignBoardUI* SignBoardUI = Cast<UDZSignBoardUI>(SignBoardWidgetComponent->GetWidget());
	if (!IsValid(SignBoardUI)) return;
	
	SignBoardUI->LevelUiUpdate(CurrentLevel);
	SignBoardUI->SetVisibility(ESlateVisibility::Visible);
}

#pragma endregion
//======================================================================================================================	