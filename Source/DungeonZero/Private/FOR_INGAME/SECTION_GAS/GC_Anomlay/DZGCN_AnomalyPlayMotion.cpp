// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyPlayMotion.h"

#include "FOR_INGAME/SECTION_ANOMALY/Interface/DZAnomalyMotionInterface.h"


// Sets default values
ADZGCN_AnomalyPlayMotion::ADZGCN_AnomalyPlayMotion()
{
	bAutoDestroyOnRemove = true;
}

bool ADZGCN_AnomalyPlayMotion::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnActive_Implementation(MyTarget, Parameters);
	// UDZAnomalyMotionInterface 상속 받은 액터만 진행
	if (!MyTarget->Implements<UDZAnomalyMotionInterface>())
	{
		return false;
	}
	IDZAnomalyMotionInterface::Execute_StartAnomalyMotion(MyTarget);
	return true;
}

bool ADZGCN_AnomalyPlayMotion::WhileActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::WhileActive_Implementation(MyTarget, Parameters);
	
	if (!MyTarget->Implements<UDZAnomalyMotionInterface>())
	{
		return false;
	}
	IDZAnomalyMotionInterface::Execute_StartAnomalyMotion(MyTarget);

	return true;
}

bool ADZGCN_AnomalyPlayMotion::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	Super::OnRemove_Implementation(MyTarget, Parameters);
	// UDZAnomalyMotionInterface 상속 받은 액터만 진행
	if (!MyTarget->Implements<UDZAnomalyMotionInterface>())
	{
		return false;
	}
	IDZAnomalyMotionInterface::Execute_StopAnomalyMotion(MyTarget);

	return true;
}
