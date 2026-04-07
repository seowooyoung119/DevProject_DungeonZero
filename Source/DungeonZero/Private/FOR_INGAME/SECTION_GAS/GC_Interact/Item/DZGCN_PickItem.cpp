// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Interact/Item/DZGCN_PickItem.h"
#include "FOR_INGAME/SECTION_SOUND/Item/System/DZITemSoundSystem.h"
#include "Kismet/GameplayStatics.h"

UDZGCN_PickItem::UDZGCN_PickItem()
{
}

bool UDZGCN_PickItem::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	Super::OnExecute_Implementation(MyTarget, Parameters);
	
	// 아이템 사운드 매니저 가져오기 
	UDZITemSoundSystem* ItemSoundSystem = UDZITemSoundSystem::Get(this);
	if (!IsValid(ItemSoundSystem)) return false;
	
	// 아이템 사운드 로드 : RawMagnitude 을 스태틱 ID 넘겨주는 것으로 쓰는 중!
	int32 ItemID = static_cast<int32>(Parameters.RawMagnitude);
	FDZItemPickUpSoundTable* PickSoundTable = ItemSoundSystem->GetItemPickUpSoundTable(ItemID);
	if (!PickSoundTable) return false;
	
	USoundBase* LoadSound = PickSoundTable->PickUpSound.LoadSynchronous();
	if (!IsValid(LoadSound)) return false;
	
	UGameplayStatics::PlaySoundAtLocation(MyTarget, LoadSound, MyTarget->GetActorLocation());
	
	return true;
}