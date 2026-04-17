// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/Actor/DZCampfireActor.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/TorchLight/DZTorchLight.h"


ADZCampfireActor::ADZCampfireActor()
{
	CampfireMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CampfireMeshComp"));
	RootComponent = CampfireMeshComp;
	
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(CampfireMeshComp);

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(CampfireMeshComp);
}

void ADZCampfireActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADZCampfireActor::ToggleInteractWidget_Implementation(bool InWantOn)
{
	IDZCommonInteractInterface::ToggleInteractWidget_Implementation(InWantOn);
}

void ADZCampfireActor::DoStandAloneInteractLogic_Implementation(FDZInteractData& InteractData)
{
	AActor* InstigatorActor = InteractData.Instigator;
	if (!IsValid(InstigatorActor))
	{
		return;
	}
	TArray<AActor*> AttachedActors;
	InstigatorActor->GetAttachedActors(AttachedActors);

	for (AActor* Actor : AttachedActors)
	{
		if (ADZTorchLight* Torch = Cast<ADZTorchLight>(Actor))
		{
			Torch->TorchCharge();
			break;
		}
	}
}

