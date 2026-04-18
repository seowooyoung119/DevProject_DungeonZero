// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/Library/UpdateSenseLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"

void UUpdateSenseLibrary::UpdateHearingRange(UAIPerceptionComponent* PerceptionComponent, float NewRange, float LoseHearRadius)
{
	if (!IsValid(PerceptionComponent))
	{
		return;
	}
	
	// 청각 가져오기 
	FAISenseID SenseID = UAISense::GetSenseID<UAISense_Hearing>();
	UAISenseConfig* Config = PerceptionComponent->GetSenseConfig(SenseID);
	if (!IsValid(Config))
	{
		return;
	}
	UAISenseConfig_Hearing* HearingConfig = Cast<UAISenseConfig_Hearing>(Config);
	if (!IsValid(HearingConfig))
	{
		return;
	}

	// 거리 수정 
	HearingConfig->HearingRange = NewRange;
	HearingConfig->LoSHearingRange = LoseHearRadius;
			
	// 변경된 설정을 퍼셉션 시스템에 재등록
	PerceptionComponent->ConfigureSense(*HearingConfig);
}

void UUpdateSenseLibrary::UpdateSightRange(UAIPerceptionComponent* PerceptionComponent, float NewRange, float LoseSightRadius)
{
	if (!IsValid(PerceptionComponent))
	{
		return;
	}

	// 시각 가져오기 
	FAISenseID SenseID = UAISense::GetSenseID<UAISense_Sight>();
	UAISenseConfig* Config = PerceptionComponent->GetSenseConfig(SenseID);
	if (!IsValid(Config))
	{
		return;
	}
	UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(Config);
	if (!IsValid(SightConfig))
	{
		return;
	}
	
	// 시야 거리 업데이트
	SightConfig->SightRadius = NewRange;
	SightConfig->LoseSightRadius = LoseSightRadius; 

	// 변경된 설정을 퍼셉션 시스템에 재등록
	PerceptionComponent->ConfigureSense(*SightConfig);
}
