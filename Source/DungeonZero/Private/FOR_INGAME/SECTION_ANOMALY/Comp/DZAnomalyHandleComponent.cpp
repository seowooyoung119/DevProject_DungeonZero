// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Comp/DZAnomalyHandleComponent.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZAnomalyHandleComponent::UDZAnomalyHandleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDZAnomalyHandleComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UDZAnomalyHandleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma endregion
//======================================================================================================================	