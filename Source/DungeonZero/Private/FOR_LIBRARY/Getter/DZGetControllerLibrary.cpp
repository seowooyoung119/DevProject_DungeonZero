// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_LIBRARY/Getter/DZGetControllerLibrary.h"

APlayerController* UDZGetControllerLibrary::GetPlayerControllerFromComponent(AActor* InOwner)
{
	if (!IsValid(InOwner)) return nullptr;
	
	APawn* OwnerPawn = Cast<APawn>(InOwner);
	if (!IsValid(OwnerPawn)) return nullptr;

	AController* OwnerController = OwnerPawn->GetController();
	if (!IsValid(OwnerController)) return nullptr;
	
	APlayerController* PC = Cast<APlayerController>(OwnerController);
	if (!IsValid(PC)) return nullptr;
	
	return PC;
}
