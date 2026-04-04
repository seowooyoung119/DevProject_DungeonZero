// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZResultWayTriggerVolume.h"

#include "Components/BoxComponent.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_PLAYER/Character/DZPlayerCharacter.h"
#include "FOR_INGAME/SECTION_STAGE/System/Control/DZStageControlSystem.h"


//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━

ADZResultWayTriggerVolume::ADZResultWayTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	SetRootComponent(TriggerBoxComponent);
}

void ADZResultWayTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
	
	if (!HasAuthority()) return;
	TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADZResultWayTriggerVolume::OnBoxOverlap);
	
	// 메시지 구독
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	AllowPlayerControlListenerHandle = MessageSubsystem.RegisterListener<FDZAllowPlayerControlMSG>(DZ::PlayerMSG::DZ_PLAYER_CANMOVEANDSEE, this, &ADZResultWayTriggerVolume::OnAllowPlayerSeeAndMoveReceived);
}

void ADZResultWayTriggerVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 게임 플레이 메시지 해제
	if (UGameplayMessageSubsystem::HasInstance(this))
	{
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
		MessageSubsystem.UnregisterListener(AllowPlayerControlListenerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
	
}

#pragma endregion
//======================================================================================================================	
#pragma region 이상현상이동트리거볼륨
	
	//━━━━━━━━━━━━━━━━━━━━
	// 이상현상이동트리거볼륨
	//━━━━━━━━━━━━━━━━━━━━	

void ADZResultWayTriggerVolume::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsMoveLogicHasStart == true) return;
	
	ADZPlayerCharacter* PlayerCharacter = Cast<ADZPlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter)) return;
	
	IsMoveLogicHasStart = true;
	
	UDZStageControlSystem* StageControlSystem = UDZStageControlSystem::Get(this);
	if (!IsValid(StageControlSystem)) return;
	
	StageControlSystem->PlayerEnterTheResultWay();
}

#pragma endregion
//======================================================================================================================	
#pragma region 게임플레이메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임플레이메시지
	//━━━━━━━━━━━━━━━━━━━━

void ADZResultWayTriggerVolume::OnAllowPlayerSeeAndMoveReceived(FGameplayTag Channel, const FDZAllowPlayerControlMSG& Payload)
{
	if (Payload.CanMoveAndSee == true) IsMoveLogicHasStart = false;
}

#pragma endregion
//======================================================================================================================		
