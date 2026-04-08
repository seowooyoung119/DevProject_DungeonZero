// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Actor/StaticMeshActor/DZStaticMeshAnomalyActor.h"


ADZStaticMeshAnomalyActor::ADZStaticMeshAnomalyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MainMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMeshComp->SetupAttachment(RootComponent);
	MainMeshComp->ComponentTags.Add(TEXT("MainMesh"));
}


