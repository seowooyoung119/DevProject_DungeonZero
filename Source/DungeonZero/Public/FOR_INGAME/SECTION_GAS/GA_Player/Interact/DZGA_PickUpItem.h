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

class UDZInventoryMasterComponent;
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
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 내부처리

	//━━━━━━━━━━━━━━━━━━━━
	// 내부처리
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	// 서버
	bool AddItemToInventory_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck);
	bool AddItemToBody_internal(FDZItemRuntimeData& ItemRunTimeData, AActor* TargetItem, FDZITemStaticData& ItemStaticDataForCheck);
	
	// 클라
	bool IsItemCanAddToInventory_internal(FDZItemRuntimeData& ItemRunTimeData);
	bool IsItemCanAddToBody_internal(FDZItemRuntimeData& ItemRunTimeData);
	
	// 후처리 
	void RequestAddGameplayCue(int32 ItemID);
	
	// 브로드 캐스트 
	void BroadcastItemPickUp(const EDZInventoryCompType InventoryCompType, UDZInventoryMasterComponent* InventoryComponentPtr) const;
	
#pragma endregion
//======================================================================================================================	
#pragma region 픽업사운드

	//━━━━━━━━━━━━━━━━━━━━
	// 픽업사운드
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FGameplayTag ItemPickUpSoundGameplayCue = DZ::GameplayCue::Item::DZ_CUE_ITEM_PICKUUP;

#pragma endregion
//======================================================================================================================		
};
