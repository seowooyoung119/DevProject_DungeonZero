// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Anomaly/DZRegisterAllCanBeAnomalyActorHelperSystem.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━

UDZRegisterAllCanBeAnomalyActorHelperSystem* UDZRegisterAllCanBeAnomalyActorHelperSystem::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UDZRegisterAllCanBeAnomalyActorHelperSystem* RegisterAllCanBeAnomalyActorHelperSystem = World->GetSubsystem<UDZRegisterAllCanBeAnomalyActorHelperSystem>();
	if (!IsValid(RegisterAllCanBeAnomalyActorHelperSystem)) return nullptr;
	
	return RegisterAllCanBeAnomalyActorHelperSystem;
}

#pragma endregion
//======================================================================================================================

