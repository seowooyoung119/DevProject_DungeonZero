// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GA_Item/DZGA_IsThisAnomaly.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZFindAnomalyMSG.h"
#include "FOR_COMMON/SECTION_LOG/Item_And_Inventory/Item/DZItemLOG.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"
#include "FOR_COMMON/SECTION_TAG/Item/DZItemGATag.h"
#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"
#include "FOR_INGAME/SECTION_INTERACT/Comp/DZInteractComponent.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"

UDZGA_IsThisAnomaly::UDZGA_IsThisAnomaly()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	
	// 에셋 태그
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(DZ::Item::DZ_ITEM_ISTHISANOMALY);
	SetAssetTags(AssetTags);
	
	// 부여 태그
	ActivationOwnedTags.AddTag(DZ::Item::DZ_ITEM_ISTHISANOMALY);
}

void UDZGA_IsThisAnomaly::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	UE_LOG(DZItem_IsThisAnomalyActionLog, Log, TEXT("이게 어노말리인가? 실행"))
	
	// 인터렉트 컴포넌트 체크
	UDZInteractComponent* InteractComponent = IPlayerCompGetterInterface::Execute_GetDZInteractComponent(GetAvatarActorFromActorInfo());
	if (!IsValid(InteractComponent))
	{
		UE_LOG(DZItem_IsThisAnomalyActionLog, Log, TEXT("이게 어노말리인가? 인터렉트 컴포넌트 못찾음"))
		K2_EndAbility(); 
		return;
	}; 
	
	// 현재 보고 있는 액터 가져오기 
	AActor* CurrentInteractActor = InteractComponent->GetCurrentInteractActor();
	
	// 1. 없는 경우 
	if (CurrentInteractActor == nullptr)
	{
		UE_LOG(DZItem_IsThisAnomalyActionLog, Log, TEXT("이게 어노말리인가? 뭔가 보고 있지 않은 경우 보내기 실행"))
		FDZFindAnomalyMSG FindAnomalyMSG;
		FindAnomalyMSG.FindAnomalyActor = nullptr;
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSubsystem.BroadcastMessage(DZ::FindAnomalyMSG::DZ_SEND_FIND_ANOMLAY, FindAnomalyMSG);
		
		K2_EndAbility();
		return;
	}
	
	// 2. 있는데 인터페이스 없는 경우 
	if (!CurrentInteractActor->GetClass()->ImplementsInterface(UDZCommonPlayRoleInterface::StaticClass()))
	{
		UE_LOG(DZItem_IsThisAnomalyActionLog, Log, TEXT("이게 어노말리인가? 뭔가 보고 있는데 인터페이스도 상속 안한 녀석인 경우 보내기 실행"))
		FDZFindAnomalyMSG FindAnomalyMSG;
		FindAnomalyMSG.FindAnomalyActor = CurrentInteractActor;
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSubsystem.BroadcastMessage(DZ::FindAnomalyMSG::DZ_SEND_FIND_ANOMLAY, FindAnomalyMSG);
		
		K2_EndAbility();
		return;
	}	
		
	// 2. 있는데 인터페이스 있는데 어노말리 아닌 경우  
	EDZPlayRole CurrentInteractActorPlayRole = IDZCommonPlayRoleInterface::Execute_GetPlayRole(CurrentInteractActor);
	if (CurrentInteractActorPlayRole != EDZPlayRole::Anomaly)
	{
		UE_LOG(DZItem_IsThisAnomalyActionLog, Log, TEXT("이게 어노말리인가? 뭔가 보고 있는데 어노말리인 아닌 경우 보내기 실행"))
		FString RoleEnumString = StaticEnum<EDZPlayRole>()->GetValueAsString(CurrentInteractActorPlayRole);
		UE_LOG(LogTemp, Warning, TEXT("Current PlayRole: %s"), *RoleEnumString);
		
		FDZFindAnomalyMSG FindAnomalyMSG;
		FindAnomalyMSG.FindAnomalyActor = CurrentInteractActor;
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSubsystem.BroadcastMessage(DZ::FindAnomalyMSG::DZ_SEND_FIND_ANOMLAY, FindAnomalyMSG);
		
		K2_EndAbility();
		return;
	}
	
	// 3. 어노말리인 경우 
	if (CurrentInteractActorPlayRole == EDZPlayRole::Anomaly)
	{
		UE_LOG(DZItem_IsThisAnomalyActionLog, Log, TEXT("이게 어노말리인가? 뭔가 보고 있는데 어노말리인 경우 보내기 실행"))
		FDZFindAnomalyMSG FindAnomalyMSG;
		FindAnomalyMSG.FindAnomalyActor = CurrentInteractActor;
		UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSubsystem.BroadcastMessage(DZ::FindAnomalyMSG::DZ_SEND_FIND_ANOMLAY, FindAnomalyMSG);
	
		K2_EndAbility();
		return;
	}
	
	K2_EndAbility();
}
