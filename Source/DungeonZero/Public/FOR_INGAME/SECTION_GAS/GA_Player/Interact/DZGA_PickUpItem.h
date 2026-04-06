// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GA/DZGATag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/DZGameplayCueTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/Item/DZItemGameplayCueTag.h"
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
	
//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	UDZGA_PickUpItem();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

#pragma endregion
//======================================================================================================================	
#pragma region 내부처리

	//━━━━━━━━━━━━━━━━━━━━
	// 내부처리
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	bool AddItemToInventory_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck);
	bool AddItemToBody_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck);
	
#pragma endregion
//======================================================================================================================	
#pragma region 픽업사운드

	//━━━━━━━━━━━━━━━━━━━━
	// 픽업사운드
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FGameplayTag ItemDropSoundGameplayCue = DZ::GameplayCue::Item::DZ_CUE_ITEM_PICKUUP;

#pragma endregion
//======================================================================================================================		
};
