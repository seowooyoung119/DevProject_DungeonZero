// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DZAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)		\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)	\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)				\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)				\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region OnRep
	
	//━━━━━━━━━━━━━━━━━━━━
	// OnRep
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	
	UFUNCTION() virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION() virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION() virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);
	UFUNCTION() virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);
	UFUNCTION() virtual void OnRep_Mentality(const FGameplayAttributeData& OldMentality);
	UFUNCTION() virtual void OnRep_MaxMentality(const FGameplayAttributeData& OldMaxMentality);
	UFUNCTION() virtual void OnRep_Hunger(const FGameplayAttributeData& OldHunger);
	UFUNCTION() virtual void OnRep_MaxHunger(const FGameplayAttributeData& OldMaxHunger);
	UFUNCTION() virtual void OnRep_Thirst(const FGameplayAttributeData& OldThirst);
	UFUNCTION() virtual void OnRep_MaxThirst(const FGameplayAttributeData& OldMaxThirst);
	UFUNCTION() virtual void OnRep_Temperature(const FGameplayAttributeData& OldTemperature);

	UFUNCTION() virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UFUNCTION() virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);
	UFUNCTION() virtual void OnRep_DefensePower(const FGameplayAttributeData& OldDefensePower);
	UFUNCTION() virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
	UFUNCTION() virtual void OnRep_TotalWeight(const FGameplayAttributeData& OldTotalWeight);
	
	UFUNCTION() virtual void OnRep_SurvivalSkill(const FGameplayAttributeData& OldSurvivalSkill);
	UFUNCTION() virtual void OnRep_MovementSkill(const FGameplayAttributeData& OldMovementSkill);
	UFUNCTION() virtual void OnRep_LootingSkill(const FGameplayAttributeData& OldLootingSkill);
	UFUNCTION() virtual void OnRep_MakingSkill(const FGameplayAttributeData& OldMakingSkill);
	UFUNCTION() virtual void OnRep_FarmingSkill(const FGameplayAttributeData& OldFarmingSkill);
	UFUNCTION() virtual void OnRep_BuildingSkill(const FGameplayAttributeData& OldBuidlingSkill);
	UFUNCTION() virtual void OnRep_AimingSkill(const FGameplayAttributeData& OldAimingSkill);
	UFUNCTION() virtual void OnRep_BattleSkill(const FGameplayAttributeData& OldBattleSkill);
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;		// 값이 바뀌기 직전에 호출 
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override; // Effect(데미지, 힐 등)가 실행된 직후 호출 
	
#pragma endregion
//======================================================================================================================	
#pragma region 어트리뷰트_매크로
	
	//━━━━━━━━━━━━━━━━━━━━
	// 어트리뷰트
	//━━━━━━━━━━━━━━━━━━━━	
public:
	// 체력
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, MaxHealth);
	// 지구력
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, Stamina);
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, MaxStamina);
	// 정신력
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, Mentality);
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, MaxMentality);
	// 배고픔
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, Hunger);
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, MaxHunger);
	// 갈증
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, Thirst);
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, MaxThirst);
	// 체온
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, Temperature);

	ATTRIBUTE_ACCESSORS(UDZAttributeSet, Strength);			// 근력
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, AttackPower);		// 공격력
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, DefensePower);		// 방어력
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, MovementSpeed);	// 이동속도
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, TotalWeight)		// 총 무게 (모든 장비 다 포함)
	
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, SurvivalSkill)		// 생존 숙련도
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, LootingSkill)		// 루팅 숙련도
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, MakingSkill)		// 제작 숙련도
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, FarmingSkill)		// 농사 숙련도
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, BuildingSkill)		// 건축 숙련도
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, AimingSkill)		// 조준 숙련도
	ATTRIBUTE_ACCESSORS(UDZAttributeSet, BattleSkill)		// 전투 숙련도 
	
	
#pragma endregion
//======================================================================================================================	
#pragma region 어트리뷰트
	
	//━━━━━━━━━━━━━━━━━━━━
	// 어트리뷰트
	//━━━━━━━━━━━━━━━━━━━━	

public:

//----------------------------------------------------------------------------------------------------------------------	
	
	//-----------------------
	// 체력 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	//-----------------------
	// 지구력  
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
	FGameplayAttributeData Stamina;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	//-----------------------
	// 정신력
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mentality)
	FGameplayAttributeData Mentality;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxMentality)
	FGameplayAttributeData MaxMentality;
	//-----------------------
	// 배고픔
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Hunger)
	FGameplayAttributeData Hunger;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHunger)
	FGameplayAttributeData MaxHunger;
	//-----------------------
	// 갈증 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Thirst)
	FGameplayAttributeData Thirst;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxThirst)
	FGameplayAttributeData MaxThirst;
	//-----------------------
	// 체온
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Temperature)
	FGameplayAttributeData Temperature;
	//-----------------------
	// 근력  
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	
//----------------------------------------------------------------------------------------------------------------------	
	
	//-----------------------
	// 공격력 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	//-----------------------
	// 방어력
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_DefensePower)
	FGameplayAttributeData DefensePower;
	//-----------------------
	// 이동 속도  
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	//-----------------------
	// 무게
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_TotalWeight)
	FGameplayAttributeData TotalWeight;
	
	
//----------------------------------------------------------------------------------------------------------------------	

	//-----------------------
	// 생존 숙련도 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_SurvivalSkill)
	FGameplayAttributeData SurvivalSkill;
	//-----------------------
	// 움직임 숙련도
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MovementSkill)
	FGameplayAttributeData MovementSkill;
	//-----------------------
	// 파밍 숙련도 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_LootingSkill)
	FGameplayAttributeData LootingSkill;
	//-----------------------
	// 제작 숙련도
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MakingSkill)
	FGameplayAttributeData MakingSkill;
	//-----------------------
	// 농사 숙련도 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_FarmingSkill)
	FGameplayAttributeData FarmingSkill;
	//-----------------------
	// 건축 숙련도 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_BuildingSkill)
	FGameplayAttributeData BuildingSkill;
	//-----------------------
	// 조준 숙련도
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AimingSkill)
	FGameplayAttributeData AimingSkill;
	//-----------------------
	// 전투 숙련도 
	//-----------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_BattleSkill)
	FGameplayAttributeData BattleSkill;
	
	
#pragma endregion
//======================================================================================================================	
		
};
