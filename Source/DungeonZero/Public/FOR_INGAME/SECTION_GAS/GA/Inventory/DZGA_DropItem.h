// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_GAS/GA/A_Base/DZGA_BaseAbility.h"
#include "DZGA_DropItem.generated.h"

/**
 * 현재 손에 든 아이템을 버리는 어빌리티 
 * NOTE :: 인풋핸들컴포넌트에서 try 로 발동시키며, 이전에 현재 액티핫키인덱스(레플리케이트 변수) 체크한 후 실제로 유효할 때만 발동함. 
 */
UCLASS()
class DUNGEONZERO_API UDZGA_DropItem : public UDZGA_BaseAbility
{
	GENERATED_BODY()
	
public:
	UDZGA_DropItem();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
