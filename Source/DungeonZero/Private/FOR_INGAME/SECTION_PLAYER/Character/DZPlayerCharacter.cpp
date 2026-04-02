// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_PLAYER/Character/DZPlayerCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "DungeonZero/Public/FOR_INGAME/SECTION_GAS/Data/Asset/DZGiveGAGEDataAsset.h"
#include "DungeonZero/Public/FOR_INGAME/SECTION_INPUT/Comp/DZInputHandleComponent.h"
#include "FOR_INGAME/SECTION_INTERACT/Comp/DZInteractComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/EquipVisual/Comp/HotKey/DZHotKeyEquipVisualComponent.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/HotKey/DZHotKeyInventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpringArmComponent.h"

//======================================================================================================================	
#pragma region OnRep
	
	//━━━━━━━━━━━━━━━━━━━━
	// OnRep
	//━━━━━━━━━━━━━━━━━━━━
	
void ADZPlayerCharacter::OnRep_JobRole()
{
	
}

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//──────────────
	// 라이프 사이클 
	//──────────────

ADZPlayerCharacter::ADZPlayerCharacter()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;
	
	// net
	bReplicates = true;
	SetReplicatingMovement(true);
	SetNetUpdateFrequency(100.f);
	SetMinNetUpdateFrequency(100.f);
	
	// 카메라와 스프링 암 
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	
	// 회전 관련 설정 
	{
		// 1. 캐릭터 몸체가 컨트롤러의 Yaw(좌우 회전) 값을 그대로 따르도록 설정
		bUseControllerRotationYaw = true;		// true: 마우스 돌리면 캐릭터 몸도 같이 돌아감
		bUseControllerRotationPitch = false;	// 보통 위아래는 캐릭터 몸이 숙여지면 이상하므로 false
		bUseControllerRotationRoll = false;

		// 2. 캐릭터 무브먼트 컴포넌트 설정 변경
		GetCharacterMovement()->bOrientRotationToMovement = false;		// 이동 방향으로 몸 돌리기 끄기
		GetCharacterMovement()->bUseControllerDesiredRotation = false;	// 부드러운 회전 보간 사용 안 함 (즉각 반응 위해) (bUseControllerRotationYaw 켜져 있으면 효과 없음)

		// 3. 스프링 암 설정 (카메라 회전 관련)
		SpringArmComponent->bUsePawnControlRotation = true; // 카메라가 컨트롤러 회전을 따르게 함
	}
	
	// interact
	InteractComponent = CreateDefaultSubobject<UDZInteractComponent>(TEXT("InteractComponent"));
	
	// input
	InputHandleComponent = CreateDefaultSubobject<UDZInputHandleComponent>(TEXT("InputHandleComponent"));
	
	// 핫키 
	HotKeyInventoryComponent = CreateDefaultSubobject<UDZHotKeyInventoryComponent>(TEXT("HotKeyInventoryComponent"));
	
	// 핫키 비쥬얼
	HotKeyEquipVisualComponent = CreateDefaultSubobject<UDZHotKeyEquipVisualComponent>(TEXT("HotKeyEquipVisualComponent"));
	
	// 기본 밝기 시야 
	BaseViewLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("BaseViewLightComponent"));
	BaseViewLightComponent->SetupAttachment(CameraComponent);
}

void ADZPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// IMC 등록, IA 바인딩
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	if (IsValid(InputHandleComponent)) InputHandleComponent->SetupInput(EnhancedInputComponent);
}

void ADZPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// 컨트롤러 검사 
	if (!IsValid(NewController)) return;
	APlayerController* PC = Cast<APlayerController>(NewController);
	if (!IsValid(PC)) return;

	// GA 초기화 
	if (!IsValid(GetPlayerState())) return;
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPlayerState());
	if (!IsValid(ASC)) return;
	ASC->InitAbilityActorInfo(GetPlayerState(), this);
	// GA 부여
	InitGAS_internal(ASC);
	
	// 기본 밝기 시야 초기화
	InitializeBaseViewLightComponent_internal();
}

void ADZPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// GA 초기화 
	if (!IsValid(GetPlayerState()))return;
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPlayerState());
	if (!IsValid(ASC)) return;
	ASC->InitAbilityActorInfo(GetPlayerState(), this);
	
	// 기본 밝기 시야 초기화
	InitializeBaseViewLightComponent_internal();
}

#pragma endregion
//======================================================================================================================	
#pragma region GAS_섹션
	//━━━━━━━━━━━━━━━━━━━━
	// GAS
	//━━━━━━━━━━━━━━━━━━━━

void ADZPlayerCharacter::InitGAS_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !IsValid(BaseGAGEData)) return;
	for (auto& GA : BaseGAGEData->BaseGameplayAbilities)
	{
		if (!IsValid(GA)) continue;
		FGameplayAbilitySpec AbilitySpec(GA, 1, INDEX_NONE, this);
		InASC->GiveAbility(AbilitySpec);
	}
}

UAbilitySystemComponent* ADZPlayerCharacter::GetAbilitySystemComponent() const
{
	if (!IsValid(GetPlayerState())) return nullptr;
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPlayerState());
	if (!IsValid(ASC)) return nullptr;
	return ASC;
}

#pragma endregion
//======================================================================================================================
#pragma region 기본 시야 밝기
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인벤토리_비쥬얼
	//━━━━━━━━━━━━━━━━━━━━	

void ADZPlayerCharacter::InitializeBaseViewLightComponent_internal()
{
	// 로컬 플레이어 체크
	if (IsLocallyControlled())
	{
		BaseViewLightComponent->SetHiddenInGame(false);
	}
	else
	{
		BaseViewLightComponent->SetHiddenInGame(true);
	}
}


#pragma endregion
//======================================================================================================================	