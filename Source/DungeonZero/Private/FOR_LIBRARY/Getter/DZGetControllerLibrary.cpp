// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_LIBRARY/Getter/DZGetControllerLibrary.h"

APlayerController* UDZGetControllerLibrary::GetPlayerControllerFromComponent(AActor* InOwner)
{
	// 오너 체크
	if (!IsValid(InOwner)) return nullptr;
	
	// 오너 폰으로 캐스팅
	APawn* OwnerPawn = Cast<APawn>(InOwner);
	if (!IsValid(OwnerPawn)) return nullptr;

	// 컨트롤러 가져오기
	AController* OwnerController = OwnerPawn->GetController();
	if (!IsValid(OwnerController)) return nullptr;
	
	// 플레이어 컨트롤러 캐스팅
	APlayerController* PC = Cast<APlayerController>(OwnerController);
	if (!IsValid(PC)) return nullptr;
	
	// 반환
	return PC;
}

APlayerController* UDZGetControllerLibrary::GetPlayerControllerFromActor(AActor* InOwner)
{
	// 오너 폰으로 캐스팅
	APawn* OwnerPawn = Cast<APawn>(InOwner);
	if (!IsValid(OwnerPawn)) return nullptr;

	// 컨트롤러 가져오기
	AController* OwnerController = OwnerPawn->GetController();
	if (!IsValid(OwnerController)) return nullptr;
	
	// 플레이어 컨트롤러 캐스팅
	APlayerController* PC = Cast<APlayerController>(OwnerController);
	if (!IsValid(PC)) return nullptr;
	
	// 반환
	return PC;
}
