// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/Library/DZAIDataTableLogLibrary.h"

void UDZAIDataTableLogLibrary::LogAIData_Lib(const FDZAIClassTable* InAIClassTable)
{
	if (!InAIClassTable) return;
	
    const FDZAIClassTable& Info = *InAIClassTable;

    UE_LOG(LogTemp, Log, TEXT("=================================================="));
    UE_LOG(LogTemp, Log, TEXT("[AI Static Data Log]"));
    
    // 1. 기본 정보 (ID, Name)
    UE_LOG(LogTemp, Log, TEXT("AI ID: %d"), Info.AIClassID);

    // 2. 클래스 정보 (TSubclassOf)
    FString ClassName = Info.AIClass ? Info.AIClass->GetName() : TEXT("Null");
    UE_LOG(LogTemp, Log, TEXT("AI Class: %s"), *ClassName);

    UE_LOG(LogTemp, Log, TEXT("=================================================="));
	
}
