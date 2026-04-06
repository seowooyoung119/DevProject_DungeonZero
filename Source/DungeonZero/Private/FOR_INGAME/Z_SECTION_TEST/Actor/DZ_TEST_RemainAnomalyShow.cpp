// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/Z_SECTION_TEST/Actor/DZ_TEST_RemainAnomalyShow.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZStageMSG.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "Components/WidgetComponent.h"
#include "FOR_INGAME/Z_SECTION_TEST/UI/DZ_TEST_RemainAnomalyShowUI.h"


//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━
	
void ADZ_TEST_RemainAnomalyShow::OnRep_RemainAnomalyCount()
{
	if (!IsValid(SignBoardWidgetComponent)) return;
	UDZ_TEST_RemainAnomalyShowUI* SignBoardUI = Cast<UDZ_TEST_RemainAnomalyShowUI>(SignBoardWidgetComponent->GetWidget());
	if (!IsValid(SignBoardUI)) return;
	SignBoardUI->UpdateRemainAnomaly(RemainAnomalyCount);
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━			


ADZ_TEST_RemainAnomalyShow::ADZ_TEST_RemainAnomalyShow()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;
	
	// 컴포넌트 구성
	SignBoardRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootScene"));
	SetRootComponent(SignBoardRoot);
	
	SignBoardWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SignBoardWidgetComponent"));
	SignBoardWidgetComponent->SetupAttachment(SignBoardRoot);
}

void ADZ_TEST_RemainAnomalyShow::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZ_TEST_RemainAnomalyShow, RemainAnomalyCount);
}

void ADZ_TEST_RemainAnomalyShow::BeginPlay()
{
	Super::BeginPlay();
		
	// 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	RemainAnomalyListenerHandle = MessageSubsystem.RegisterListener<FDZStageRemainAnomalyMSG>(DZ::StageMSG::DZ_STAGE_REMAINANOMLAY_NOTICE, this, &ADZ_TEST_RemainAnomalyShow::OnReMainAnomalyReceived);

}

void ADZ_TEST_RemainAnomalyShow::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(RemainAnomalyListenerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================	
#pragma region 테스팅
	
	//━━━━━━━━━━━━━━━━━━━━
	// 테스팅
	//━━━━━━━━━━━━━━━━━━━━	

void ADZ_TEST_RemainAnomalyShow::OnReMainAnomalyReceived(FGameplayTag Channel, const FDZStageRemainAnomalyMSG& Payload)
{
	if (!IsValid(SignBoardWidgetComponent)) return;
	UDZ_TEST_RemainAnomalyShowUI* SignBoardUI = Cast<UDZ_TEST_RemainAnomalyShowUI>(SignBoardWidgetComponent->GetWidget());
	if (!IsValid(SignBoardUI)) return;
	SignBoardUI->UpdateRemainAnomaly(Payload.StageRemainAnomaly);
	
	RemainAnomalyCount = Payload.StageRemainAnomaly;	
}
#pragma endregion
//======================================================================================================================	