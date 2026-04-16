// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Actor/StaticMeshActor/DZStaticMeshAnomalyActor.h"


ADZStaticMeshAnomalyActor::ADZStaticMeshAnomalyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MainMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	SetRootComponent(MainMeshComp);
	MainMeshComp->ComponentTags.Add(TEXT("MainMesh"));
	MainMeshComp->SetIsReplicated(true);
}


