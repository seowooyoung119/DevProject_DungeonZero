// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Actor/Z_Change/DZAnomalyChangeBase.h"

ADZAnomalyChangeBase::ADZAnomalyChangeBase()
{
	PrimaryActorTick.bCanEverTick = true; // Tick 기능 자체는 사용 가능하게 설정
	PrimaryActorTick.bStartWithTickEnabled = false; // 시작은 비활성화
	
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);
	
	ChangeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChangeMeshComp"));
	ChangeMeshComp->SetupAttachment(RootScene);
	
	OriginMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OriginMeshComp"));
	OriginMeshComp->SetupAttachment(RootScene);
}
