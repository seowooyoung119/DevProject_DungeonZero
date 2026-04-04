// All CopyRight by BooZaGameStudio // 


#include "DZAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

//======================================================================================================================	
#pragma region OnRep
	
	//━━━━━━━━━━━━━━━━━━━━
	// OnRep
	//━━━━━━━━━━━━━━━━━━━━	

// OnRep 구현부 (매크로 활용)
void UDZAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, Health, OldHealth); }
void UDZAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, MaxHealth, OldMaxHealth); }
void UDZAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, Stamina, OldStamina); }
void UDZAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, MaxStamina, OldMaxStamina); }
void UDZAttributeSet::OnRep_Mentality(const FGameplayAttributeData& OldMentality) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, Mentality, OldMentality); }
void UDZAttributeSet::OnRep_MaxMentality(const FGameplayAttributeData& OldMaxMentality) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, MaxMentality, OldMaxMentality); }
void UDZAttributeSet::OnRep_Hunger(const FGameplayAttributeData& OldHunger) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, Hunger, OldHunger); }
void UDZAttributeSet::OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, MaxHunger, OldMaxHunger); }
void UDZAttributeSet::OnRep_Thirst(const FGameplayAttributeData& OldThirst) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, Thirst, OldThirst); }
void UDZAttributeSet::OnRep_MaxThirst(const FGameplayAttributeData& OldMaxThirst) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, MaxThirst, OldMaxThirst); }
void UDZAttributeSet::OnRep_Temperature(const FGameplayAttributeData& OldTemperature) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, Temperature, OldTemperature); }

void UDZAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, Strength, OldStrength); }
void UDZAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, AttackPower, OldAttackPower); }
void UDZAttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldDefensePower) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, DefensePower, OldDefensePower); }
void UDZAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, MovementSpeed, OldMovementSpeed); }
void UDZAttributeSet::OnRep_TotalWeight(const FGameplayAttributeData& OldTotalWeight) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldTotalWeight); }

void UDZAttributeSet::OnRep_SurvivalSkill(const FGameplayAttributeData& OldSurvivalSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldSurvivalSkill); }
void UDZAttributeSet::OnRep_MovementSkill(const FGameplayAttributeData& OldMovementSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldMovementSkill); }
void UDZAttributeSet::OnRep_LootingSkill(const FGameplayAttributeData& OldLootingSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldLootingSkill); }
void UDZAttributeSet::OnRep_MakingSkill(const FGameplayAttributeData& OldMakingSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldMakingSkill); }
void UDZAttributeSet::OnRep_FarmingSkill(const FGameplayAttributeData& OldFarmingSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldFarmingSkill); }
void UDZAttributeSet::OnRep_BuildingSkill(const FGameplayAttributeData& OldBuidlingSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldBuidlingSkill); }
void UDZAttributeSet::OnRep_AimingSkill(const FGameplayAttributeData& OldAimingSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldAimingSkill); }
void UDZAttributeSet::OnRep_BattleSkill(const FGameplayAttributeData& OldBattleSkill) { GAMEPLAYATTRIBUTE_REPNOTIFY(UDZAttributeSet, TotalWeight, OldBattleSkill); }

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZAttributeSet::UDZAttributeSet()
{
	// 초기값 기본 세팅
	InitHealth(100.f);		InitMaxHealth(100.f);
	InitStamina(100.f);		InitMaxStamina(100.f);
	InitMentality(100.f);	InitMaxMentality(100.f);
	InitHunger(100.f);		InitMaxHunger(100.f);
	InitThirst(100.f);		InitMaxThirst(100.f);
	InitTemperature(36.5f); 

	InitStrength(10.f);
	InitAttackPower(10.f);
	InitDefensePower(10.f);
	InitMovementSpeed(500.f);
	InitTotalWeight(0.f);
}

void UDZAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	// 모든 스탯 복제 등록
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, Mentality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MaxMentality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, Hunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MaxHunger, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, Thirst, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MaxThirst, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, Temperature, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, DefensePower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, TotalWeight, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, SurvivalSkill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MovementSkill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, LootingSkill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, MakingSkill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, FarmingSkill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, BuildingSkill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, AimingSkill, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UDZAttributeSet, BattleSkill, COND_None, REPNOTIFY_Always);
	
}

void UDZAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UDZAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	// 이펙트 적용 후 최종 클램핑 확실히 처리
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute()) SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	else if (Data.EvaluatedData.Attribute == GetMentalityAttribute()) SetMentality(FMath::Clamp(GetMentality(), 0.f, GetMaxMentality()));
	else if (Data.EvaluatedData.Attribute == GetHungerAttribute()) SetHunger(FMath::Clamp(GetHunger(), 0.f, GetMaxHunger()));
	else if (Data.EvaluatedData.Attribute == GetThirstAttribute()) SetThirst(FMath::Clamp(GetThirst(), 0.f, GetMaxThirst()));
}

#pragma endregion
//======================================================================================================================	