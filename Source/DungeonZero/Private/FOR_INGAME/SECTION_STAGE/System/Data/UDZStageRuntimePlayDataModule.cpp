// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_STAGE/System/Data/UDZStageRuntimePlayDataModule.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━
UUDZStageRuntimePlayDataModule* UUDZStageRuntimePlayDataModule::Get(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;
	
	const UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;
	
	UUDZStageRuntimePlayDataModule* StageDataModule = World->GetSubsystem<UUDZStageRuntimePlayDataModule>();
	if (!IsValid(StageDataModule)) return nullptr;
	
	return StageDataModule;
}

#pragma endregion
//======================================================================================================================	
#pragma region Data
	
	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━

bool UUDZStageRuntimePlayDataModule::HandleIsThereAnyAnomaly(AActor* InTargetActor)
{
	// Remove는 삭제에 성공하면 삭제된 요소의 개수(int32)를 반환합니다.
	// 0보다 크면 성공적으로 찾아서 지웠다는 뜻입니다.
	return AnomalyActors.Remove(InTargetActor) > 0;
}

#pragma endregion
//======================================================================================================================	