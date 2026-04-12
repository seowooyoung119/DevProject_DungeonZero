// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Comp/DZAnomalyTriggerComponent.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GA/DZGATag.h"
#include "FOR_INGAME/SECTION_PLAYER/Character/DZPlayerCharacter.h"

//======================================================================================================================
#pragma region 라이프_사이클

//──────────────
// 라이프_사이클
//──────────────
UDZAnomalyTriggerComponent::UDZAnomalyTriggerComponent()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(this);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}
#pragma endregion
//======================================================================================================================
#pragma region 트리거

//──────────────
// 트리거
//──────────────
void UDZAnomalyTriggerComponent::SetupTrigger(UAbilitySystemComponent* InASC,
	const FGameplayAbilitySpecHandle& InHandle, bool bInActivateOnTrigger, bool bInDeactivateOnTrigger)
{
	WeakASC = InASC;
	AbilitySpecHandle = InHandle;
	bActivateOnTrigger = bInActivateOnTrigger;
	bDeactivateOnTrigger = bInDeactivateOnTrigger;

	if (bActivateOnTrigger)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UDZAnomalyTriggerComponent::OnTriggerBeginOverlap);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &UDZAnomalyTriggerComponent::OnTriggerEndOverlap);
	}
	else
	{
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void UDZAnomalyTriggerComponent::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	if (!IsValid(OtherActor) || !OtherActor->IsA<ADZPlayerCharacter>())
	{
		return;
	}
	if (!WeakASC.IsValid())
	{
		return;
	}

	OverlappingPlayers++;
	if (OverlappingPlayers == 1)
	{
		FGameplayEventData EventData;
		EventData.Instigator = OtherActor;
		WeakASC->HandleGameplayEvent(DZ::GA::DZ_GA_ANOMALY_EVENTTRIGGER, &EventData);
	}
}

void UDZAnomalyTriggerComponent::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	if (!IsValid(OtherActor) || !OtherActor->IsA<ADZPlayerCharacter>())
	{
		return;
	}
	if (!bDeactivateOnTrigger)
	{
		return;
	}
	if (!WeakASC.IsValid())
	{
		return;
	}

	OverlappingPlayers = FMath::Max(0, OverlappingPlayers - 1);
	if (OverlappingPlayers == 0)
	{
		WeakASC->CancelAbilityHandle(AbilitySpecHandle);
	}
}
#pragma endregion
//======================================================================================================================


