// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Actor/SkeletalMeshActor/DZSkeletalMeshAnomalyActor.h"


ADZSkeletalMeshAnomalyActor::ADZSkeletalMeshAnomalyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	MainMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainMesh"));
	SetRootComponent(MainMeshComp);
	MainMeshComp->ComponentTags.Add(TEXT("MainMesh"));
}


