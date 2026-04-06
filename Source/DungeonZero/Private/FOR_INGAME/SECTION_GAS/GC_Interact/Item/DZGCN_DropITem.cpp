// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Interact/Item/DZGCN_DropITem.h"
#include "FOR_INGAME/SECTION_SOUND/Item/System/DZITemSoundSystem.h"
#include "Kismet/GameplayStatics.h"

UDZGCN_DropITem::UDZGCN_DropITem()
{
}

bool UDZGCN_DropITem::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	Super::OnExecute_Implementation(MyTarget, Parameters);
	
	// 아이템 사운드 매니저 가져오기 
	UDZITemSoundSystem* ItemSoundSystem = UDZITemSoundSystem::Get(this);
	if (!IsValid(ItemSoundSystem)) return false;
	
	// 아이템 사운드 로드 : RawMagnitude 을 스태틱 ID 넘겨주는 것으로 쓰는 중!
	int32 ItemID = static_cast<int32>(Parameters.RawMagnitude);
	FDZItemDropSoundTable* DropSoundTable = ItemSoundSystem->GetItemDropSoundTable(ItemID);
	if (!DropSoundTable)  return false;
	
	USoundBase* LoadSound = DropSoundTable->DropSound.LoadSynchronous();
	if (!IsValid(LoadSound))  return false;
	
	UGameplayStatics::PlaySoundAtLocation(MyTarget, LoadSound, MyTarget->GetActorLocation());
	
	UE_LOG(LogTemp, Warning, TEXT("DropSound"));
	
	return true;
}
