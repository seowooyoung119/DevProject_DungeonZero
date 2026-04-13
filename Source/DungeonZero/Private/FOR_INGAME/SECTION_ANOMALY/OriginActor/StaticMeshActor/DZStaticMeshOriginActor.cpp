// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/OriginActor/StaticMeshActor/DZStaticMeshOriginActor.h"


// Sets default values
ADZStaticMeshOriginActor::ADZStaticMeshOriginActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MainMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	SetRootComponent(MainMeshComp);
	MainMeshComp->ComponentTags.Add(TEXT("MainMesh"));
}


