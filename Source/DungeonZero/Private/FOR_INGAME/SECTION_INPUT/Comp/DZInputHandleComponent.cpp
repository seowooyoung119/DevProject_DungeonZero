// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_INPUT/Comp/DZInputHandleComponent.h"
#include "DungeonZero/Public/FOR_INGAME/SECTION_INPUT/Data/Asset/DZInputDataAsset.h"
#include "DungeonZero/Public/FOR_COMMON/SECTION_TAG/GAS/Movement/DZMovementTag.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/interface/DZCommonPlayRoleInterface.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Interact/DZInteractTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/RightClick/DZRightClickTag.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZHotKeyTag.h"
#include "FOR_COMMON/SECTION_TAG/Inventory/DZInventoryChannel.h"
#include "FOR_INGAME/SECTION_INTERACT/Comp/DZInteractComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "FOR_INGAME/SECTION_PLAYER/Interface/PlayerCompGetterInterface.h"


//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
UDZInputHandleComponent::UDZInputHandleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부_API
	//━━━━━━━━━━━━━━━━━━━━	

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
		if (IsValid(InputData->IA_InteractByRightClick)) InEnhancedInputComponent->BindAction(InputData->IA_InteractByRightClick, ETriggerEvent::Started, this, &UDZInputHandleComponent::InteractByRightClick_internal);
		if (IsValid(InputData->IA_SpecialInteract)) InEnhancedInputComponent->BindAction(InputData->IA_SpecialInteract, ETriggerEvent::Started, this, &UDZInputHandleComponent::SpecialInteract_internal);
		if (IsValid(InputData->IA_PickUpItem)) InEnhancedInputComponent->BindAction(InputData->IA_PickUpItem, ETriggerEvent::Started, this, &UDZInputHandleComponent::PickUpItem_internal);
		if (IsValid(InputData->IA_DropItem)) InEnhancedInputComponent->BindAction(InputData->IA_DropItem, ETriggerEvent::Started, this, &UDZInputHandleComponent::DropItem_internal);
	}

	// HotKey
	{
		if (IsValid(InputData->HotKeyIMC)) EISubsystem->AddMappingContext(InputData->HotKeyIMC, 0);
		if (IsValid(InputData->IA_HotkeyInteract1)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract1, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal1);
		if (IsValid(InputData->IA_HotkeyInteract2)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract2, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal2);
		if (IsValid(InputData->IA_HotkeyInteract3)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract3, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal3);
		if (IsValid(InputData->IA_HotkeyInteract4)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract4, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal4);
		if (IsValid(InputData->IA_HotkeyInteract5)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract5, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal5);
		if (IsValid(InputData->IA_HotkeyInteract6)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract6, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal6);
		if (IsValid(InputData->IA_HotkeyInteract7)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract7, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal7);
		if (IsValid(InputData->IA_HotkeyInteract8)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract8, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal8);
		if (IsValid(InputData->IA_HotkeyInteract9)) InEnhancedInputComponent->BindAction(InputData->IA_HotkeyInteract9, ETriggerEvent::Started, this, &UDZInputHandleComponent::HotKey_internal9);
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

#pragma endregion
//======================================================================================================================	
#pragma region 움직임_관련
	
	//━━━━━━━━━━━━━━━━━━━━
	// 움직임_관련
	//━━━━━━━━━━━━━━━━━━━━	

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

#pragma endregion
//======================================================================================================================	
#pragma region 상호작용_관련
	
	//━━━━━━━━━━━━━━━━━━━━
	// 상호작용_관련
	//━━━━━━━━━━━━━━━━━━━━	

void UDZInputHandleComponent::InteractByLeftClick_internal(const FInputActionValue& Value)
{
}

void UDZInputHandleComponent::InteractByRightClick_internal(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("InteractByRightClick_internal"));
	
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	// 핫키 컴포넌트 체크
	 UDZHotKeyInventoryComponent* HotKeyInventoryComponent = IPlayerCompGetterInterface::Execute_GetDZHotKeyInventoryCompo(OwnerCharacter);
	if (!IsValid(HotKeyInventoryComponent)) return; 
	
	// -1 이면 아이템 안 들고 있으므로 패스
	if (HotKeyInventoryComponent->GetActiveHotKeyIndex() == -1) return;
	
	// 인터렉트 컴포넌트 체크
	UDZInteractComponent* InteractComponent = IPlayerCompGetterInterface::Execute_GetDZInteractCompo(OwnerCharacter);
	if (!IsValid(InteractComponent)) return; 
	
	// asc 체크
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (!IsValid(ASC)) return;
	
	// 데이터 생성
	FGameplayEventData Payload;
	Payload.Instigator = ASC->GetAvatarActor();
	Payload.Target = InteractComponent->GetCurrentInteractActor();
	
	Payload.EventTag = DZ::RightClick::DZ_RIGHTCLICK_USEITEM;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ASC->GetAvatarActor(), Payload.EventTag,Payload);
}

void UDZInputHandleComponent::SpecialInteract_internal(const FInputActionValue& Value)
{
}

void UDZInputHandleComponent::PickUpItem_internal(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;

	// asc 체크
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (!IsValid(ASC)) return;

	// 인터렉트 컴포넌트 체크
	UDZInteractComponent* InteractComponent = IPlayerCompGetterInterface::Execute_GetDZInteractCompo(OwnerCharacter);
	if (!IsValid(InteractComponent)) return; 
	
	// 현재 보고 있는 액터가 있는지 체크 
	if (!IsValid(InteractComponent->GetCurrentInteractActor())) return;
	
	// 공통 인터페이스 확인
	if (!InteractComponent->GetCurrentInteractActor()->GetClass()->ImplementsInterface(UDZCommonPlayRoleInterface::StaticClass())) return;
	IDZCommonPlayRoleInterface* CommonPlayRoleInterface = CastChecked<IDZCommonPlayRoleInterface>(InteractComponent->GetCurrentInteractActor());
	if (!CommonPlayRoleInterface) return;
	
	// 데이터 생성
	FGameplayEventData Payload;
	Payload.Instigator = ASC->GetAvatarActor();
	Payload.Target = InteractComponent->GetCurrentInteractActor();
		
	switch (CommonPlayRoleInterface->Execute_GetPlayRole(InteractComponent->GetCurrentInteractActor()))
	{
		
	case EDZPlayRole::None:
		break;
		
	case EDZPlayRole::Player:
		break;
		
	case EDZPlayRole::Monster:
		break;
		
	case EDZPlayRole::Item:
		Payload.EventTag = DZ::Interact::DZ_INTERACT_PICKUPITEM;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ASC->GetAvatarActor(), Payload.EventTag,Payload);
		break;
		
	case EDZPlayRole::Anomaly:
		break;
	}
}

void UDZInputHandleComponent::DropItem_internal(const FInputActionValue& Value)
{
}

#pragma endregion
//======================================================================================================================	
#pragma region 핫키 
	
	//━━━━━━━━━━━━━━━━━━━━
	// 상호작용_관련
	//━━━━━━━━━━━━━━━━━━━━	


void UDZInputHandleComponent::HotKey_internal1(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY1.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal2(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY2.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal3(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY3.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal4(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY4.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal5(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY5.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal6(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY6.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal7(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY7.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal8(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY8.GetTag().GetSingleTagContainer());
}

void UDZInputHandleComponent::HotKey_internal9(const FInputActionValue& Value)
{
	if (!IsValid(OwnerCharacter)) return;
	if (!IsValid(OwnerController)) return;
	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerCharacter);
	if (IsValid(ASC)) ASC->TryActivateAbilitiesByTag(DZ::Inventory::DZ_INVNETORY_HOTKEY9.GetTag().GetSingleTagContainer());
}

#pragma endregion
//======================================================================================================================	
	