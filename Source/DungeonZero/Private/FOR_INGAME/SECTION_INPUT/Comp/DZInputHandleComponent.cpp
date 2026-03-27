// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_INPUT/Comp/DZInputHandleComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "DungeonZero/Public/FOR_INGAME/SECTION_INPUT/Data/Asset/DZInputDataAsset.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_ROLE/Job/DZJobRoleTag.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_TAG/GAS/Movement/DZMovementTag.h"


UDZInputHandleComponent::UDZInputHandleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDZInputHandleComponent::SetupInput(UEnhancedInputComponent* InEnhancedInputComponent)
{
	// 검증
	if (!IsValid(InEnhancedInputComponent) || !IsValid(InputData) || !IsValid(GetOwner())) return;
	
	// 플레이어 캐릭터 캐싱
	if (!CachingCharacterAndController_internal()) return;

	UEnhancedInputLocalPlayerSubsystem* EISubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(OwnerController->GetLocalPlayer());
	if (!IsValid(EISubsystem)) return;
	
	// Default Movement
	{
		if (IsValid(InputData->DefaultMovementIMC)) EISubsystem->AddMappingContext(InputData->DefaultMovementIMC, 0);
		if (IsValid(InputData->IA_Move)) InEnhancedInputComponent->BindAction(InputData->IA_Move, ETriggerEvent::Triggered, this, &UDZInputHandleComponent::Move_internal);
		if (IsValid(InputData->IA_Look)) InEnhancedInputComponent->BindAction(InputData->IA_Look, ETriggerEvent::Triggered, this, &UDZInputHandleComponent::Look_internal);
		if (IsValid(InputData->IA_Jump)) InEnhancedInputComponent->BindAction(InputData->IA_Jump, ETriggerEvent::Started, this, &UDZInputHandleComponent::Jump_internal);
	}
		
	// interact
	{
		if (IsValid(InputData->InteractIMC)) EISubsystem->AddMappingContext(InputData->InteractIMC, 0);
		if (IsValid(InputData->IA_InteractByLeftClick)) InEnhancedInputComponent->BindAction(InputData->IA_InteractByLeftClick, ETriggerEvent::Started, this, &UDZInputHandleComponent::InteractByLeftClick_internal);
	}
}

bool UDZInputHandleComponent::CachingCharacterAndController_internal()
{
	OwnerCharacter = CastChecked<ACharacter>(GetOwner());
	if (!IsValid(OwnerCharacter)) return false;
	
	if (!IsValid(OwnerCharacter->GetController())) return false;
	APlayerController* PC = CastChecked<APlayerController>(OwnerCharacter->GetController());
	if (!IsValid(PC)) return false;
	OwnerController = PC;
	
	return true;
}

void UDZInputHandleComponent::Move_internal(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	FVector2D MovementVector = Value.Get<FVector2D>();
	if(MovementVector.IsNearlyZero()) return;
	
	const FRotator Rotation = OwnerController->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	OwnerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	OwnerCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void UDZInputHandleComponent::Look_internal(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (LookAxisVector.IsNearlyZero()) return;

	OwnerCharacter->AddControllerYawInput(LookAxisVector.X);
	OwnerCharacter->AddControllerPitchInput(LookAxisVector.Y);
}

void UDZInputHandleComponent::Jump_internal(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Movement::DZ_MOVEMENT_JUMP.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::InteractByLeftClick_internal(const FInputActionValue& Value)
{
}

