// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/System/DZAISpawnSystem.h"
#include "FOR_INGAME/SECTION_AI/Data/Table/DZAIClassTable.h"
#include "FOR_INGAME/SECTION_AI/System/DZAIDataSystem.h"

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	

UDZAISpawnSystem* UDZAISpawnSystem::Get(const UObject* InWorldContextObject)
{
	if (!IsValid(InWorldContextObject))
	{
		return nullptr;
	}
	
	UWorld* World = InWorldContextObject->GetWorld();
	if (!IsValid(World))
	{
		return nullptr;
	}
	
	UGameInstance* GameInstance = World->GetGameInstance();

	UDZAISpawnSystem* AISpawnSubSystem = GameInstance->GetSubsystem<UDZAISpawnSystem>();
	if (!IsValid(AISpawnSubSystem))
	{
		return nullptr;
	}
	
	return AISpawnSubSystem;
}

#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부 API
	//━━━━━━━━━━━━━━━━━━━━

ADZAICharacterBase* UDZAISpawnSystem::SpawnNewAI(int32 InSpawnAIClassID, FVector& InSpawnLocation, FRotator& InSpawnRotation)
{
	// 정적 데이터 가져오기
	UDZAIDataSystem* AIDataSubSystem = UDZAIDataSystem::Get(this);
	if (!IsValid(AIDataSubSystem))
	{
		return nullptr;
	}
	
	FDZAIClassTable* ClassTable = AIDataSubSystem->GetItemStaticData(InSpawnAIClassID);
	if (!ClassTable)
	{
		return nullptr;
	}
	
	// 월드 및 스폰할 액터 클래스 데이터 체크 
	if (!IsValid(GetWorld()))
	{
		return nullptr;
	}
	
	if (!IsValid(ClassTable->AIClass))
	{
		return nullptr;
	}
	
	// 스폰 실시 
	ADZAICharacterBase* SpawnedItemActor = GetWorld()->SpawnActor<ADZAICharacterBase>(ClassTable->AIClass, InSpawnLocation, InSpawnRotation);
	if (!IsValid(SpawnedItemActor)) return nullptr;
	
	return SpawnedItemActor;
}

#pragma endregion
//======================================================================================================================	