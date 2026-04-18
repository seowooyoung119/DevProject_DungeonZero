// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_AI/Character/DZAICharacterBase.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DZAISpawnSystem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAISpawnSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 게터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게터
	//━━━━━━━━━━━━━━━━━━━━	
public:

	static UDZAISpawnSystem* Get(const UObject* InWorldContextObject);
	
#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부 API
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	// 새로운 AI 생성할 때 호출 
	ADZAICharacterBase* SpawnNewAI(int32 InSpawnAIClassID, FVector& InSpawnLocation, FRotator& InSpawnRotation);	
	
#pragma endregion
//======================================================================================================================			
};
