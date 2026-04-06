// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/Item/DZItemGameplayCueTag.h"
#include "FOR_INGAME/SECTION_GAS/GA_Player/A_Base/DZGA_BaseAbility.h"
#include "DZGA_DropItem.generated.h"

/**
 * 현재 손에 든 아이템을 버리는 어빌리티 
 * NOTE :: 인풋핸들컴포넌트에서 try 로 발동시키며, 이전에 현재 액티핫키인덱스(레플리케이트 변수) 체크한 후 실제로 유효할 때만 발동함. 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_DropItem : public UDZGA_BaseAbility
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		
public:
	UDZGA_DropItem();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 드랍사운드

	//━━━━━━━━━━━━━━━━━━━━
	// 드랍사운드
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FGameplayTag ItemDropSoundGameplayCue = DZ::GameplayCue::Item::DZ_CUE_ITEM_DROP;

#pragma endregion
//======================================================================================================================
	
};
