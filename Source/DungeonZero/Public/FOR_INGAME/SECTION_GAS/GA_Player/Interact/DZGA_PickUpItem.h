// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZItemRuntimeData.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Data/Struct/DZITemStaticData.h"
#include "DZGA_PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_PickUpItem : public UDZGA_BaseAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_PickUpItem();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:
	bool AddItemToInventory_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck);
	bool AddItemToBody_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck);
	
};
