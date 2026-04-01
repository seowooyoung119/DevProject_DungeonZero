// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_INTERACT/Library/DZInteractDebugLibrary.h"

void UDZInteractDebugLibrary::DebugInteractActors(const AActor* WorldContextObject, AActor* Current, AActor* Last)
{
	// 체크
	if (!IsValid(WorldContextObject)) return;

	// 서버 체크
	FString RoleString = WorldContextObject->HasAuthority() ? TEXT("Server") : TEXT("Client");
	
	// 현재 액터, 지난 액터 체크
	FString CurrentName = IsValid(Current) ? Current->GetName() : TEXT("None");
	FString LastName = IsValid(Last) ? Last->GetName() : TEXT("None");

	// 디버그 메시지 스트링
	FString DebugText = FString::Printf(TEXT("[%s] Interact Status\n - Current: %s\n - Last: %s"), *RoleString, *CurrentName, *LastName);

	// Key값을 지정하여 메시지 덮어씌우기 
	if (IsValid(GEngine)) GEngine->AddOnScreenDebugMessage(1101, 0.1f, FColor::Cyan, DebugText);
}
