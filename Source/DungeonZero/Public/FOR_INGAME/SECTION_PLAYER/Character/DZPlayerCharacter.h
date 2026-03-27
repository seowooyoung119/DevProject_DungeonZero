// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_ROLE/Job/DZJobRoleInterface.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_ROLE/Job/DZJobRoleTag.h"
#include "GameFramework/Character.h"
#include "DZPlayerCharacter.generated.h"

class UDZGiveGAGEDataAsset;
class UDZInteractComponent;
class UCameraComponent;
class USpringArmComponent;
class UDZInputHandleComponent;

UCLASS()
class DUNGEONZERO_API ADZPlayerCharacter : public ACharacter, public IAbilitySystemInterface, public IDZJobRoleInterface
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region OnRep
	
	//━━━━━━━━━━━━━━━━━━━━
	// OnRep
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	
	UFUNCTION() void OnRep_JobRole();

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
	
	
public:
	ADZPlayerCharacter();
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
#pragma endregion
//======================================================================================================================	
#pragma region GAS_섹션
	//━━━━━━━━━━━━━━━━━━━━
	// GAS
	//━━━━━━━━━━━━━━━━━━━━

protected:
	// IAbilitySystemInterface ~ 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;;
	// ~ IAbilitySystemInterface
	
	// GAS 관련 초기화
	virtual void InitGAS_internal(UAbilitySystemComponent* InASC, APlayerController* InPC);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " DZ")
	TObjectPtr<UDZGiveGAGEDataAsset> BaseGAGEData = nullptr;
	
#pragma endregion
//======================================================================================================================
#pragma region 인터렉트_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_섹션
	//━━━━━━━━━━━━━━━━━━━━
		
protected:
	// 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UDZInteractComponent> InteractComponent;
	
#pragma endregion
//======================================================================================================================
#pragma region 직업 
	
	//━━━━━━━━━━━━━━━━━━━━
	// 직업
	//━━━━━━━━━━━━━━━━━━━━
	
	
public:
	// IDZJobRoleInterface ~ 
	FORCEINLINE virtual FGameplayTag GetJobRoleTag_Implementation() const override { return JobRole; };
	FORCEINLINE virtual void SetJobRole_Implementation(FGameplayTag& InJobRoleTag) override { JobRole = MoveTemp(InJobRoleTag); };
	// ~ IDZJobRoleInterface
	
protected:
	// 직업
	UPROPERTY(ReplicatedUsing = OnRep_JobRole, EditAnywhere, BlueprintReadWrite, Category = "DZ")
	FGameplayTag JobRole = DZ::JobRole::DZ_JOBROLE_NONE;

#pragma endregion
//======================================================================================================================	
#pragma region 입력_섹션
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 입력_섹션
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UDZInputHandleComponent> InputHandleComponent = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region 카메라와_스프링암
	
	//━━━━━━━━━━━━━━━━━━━━
	// 카메라와_스프링암
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UCameraComponent> CameraComponent = nullptr;
	
#pragma endregion
//======================================================================================================================	
	
	
};
