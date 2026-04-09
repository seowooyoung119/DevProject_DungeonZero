// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Actor/Z_Shadow/DZAnomalyShadow.h"


ADZAnomalyShadow::ADZAnomalyShadow()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// MainMeshComp -> 오너에게만 보이게 설정 (in 에디터)
}

void ADZAnomalyShadow::BeginPlay()
{
	Super::BeginPlay();

	// 해골은 안보이지만 그림자는 보이게
	if (IsValid(MainMeshComp))
	{
		MainMeshComp->SetCastHiddenShadow(true);
	}
}
