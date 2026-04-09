// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Character/Base/DZAnomalyCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "FOR_INGAME/SECTION_GAS/Data/Asset/DZAnomalyGrantDataAsset.h"
#include "FOR_INGAME/SECTION_PLAYER/Character/DZPlayerCharacter.h"
#include "Net/UnrealNetwork.h"


//======================================================================================================================	
#pragma region 라이프_사이클

	//──────────────
	// 라이프 사이클 
	//──────────────

ADZAnomalyCharacterBase::ADZAnomalyCharacterBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;

	// rep
	bReplicates = true;
	SetReplicatingMovement(true);
	
	AnomalyAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AnomalyAbilitySystemComponent"));
	AnomalyAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

void ADZAnomalyCharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZAnomalyCharacterBase, ReplicatedAnomalyScale);
}

void ADZAnomalyCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AnomalyAbilitySystemComponent->InitAbilityActorInfo(this, this);
	
	// 리시브 데칼 설정 초기화
	SetRecieveDecals(false);
	
	if (!HasAuthority() || !IsValid(AnomalyGrantData))
	{
		return;
	}

	// 어노말리 GA 랜덤 부여
	InitGAS_internal(AnomalyAbilitySystemComponent);
	
	// 어노말리 GA 활성화 설정
	ActivateAnomaly_internal(AnomalyAbilitySystemComponent);
}

void ADZAnomalyCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 활성화된 어빌리티 정리
	if (AnomalyAbilitySystemComponent)
	{
		AnomalyAbilitySystemComponent->CancelAllAbilities();
	}
	Super::EndPlay(EndPlayReason);
}

#pragma endregion
//======================================================================================================================		
#pragma region 어노말리

	//──────────────
	// 어노말리
	//──────────────	

void ADZAnomalyCharacterBase::SetAnomalyScale(float InScale)
{
	ReplicatedAnomalyScale = InScale;
	SetActorScale3D(FVector(InScale));
}

void ADZAnomalyCharacterBase::InitGAS_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !IsValid(AnomalyGrantData)) return;

	// 랜덤한 하나의 어빌리티만 부여
	// 유효한 어빌리티로 배열 생성
	TArray<FDZAnomalyGrantData> ValidAbilities;
	for (auto& GAData : AnomalyGrantData->GrantedAbilities)
	{
		if (IsValid(GAData.GameplayAbility))
		{
			ValidAbilities.Add(GAData);
		}
	}
	const FDZAnomalyGrantData& SelectedData = ValidAbilities[FMath::RandRange(0, ValidAbilities.Num() - 1)];
	// 트리거 여부 저장
	bActivateOnTrigger = SelectedData.bActivateOnTrigger;
	bDeactivateOnTrigger = SelectedData.bDeactivateOnTrigger;
	// 어빌리티 부여
	FGameplayAbilitySpec AbilitySpec(SelectedData.GameplayAbility, 1, INDEX_NONE,
	                                 this);
	AnomalyAbilitySpecHandle = InASC->GiveAbility(AbilitySpec);
}

void ADZAnomalyCharacterBase::ActivateAnomaly_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !AnomalyAbilitySpecHandle.IsValid())
	{
		return;
	}
	if (bActivateOnTrigger)
	{
		// 오버랩 바인딩
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADZAnomalyCharacterBase::OnTriggerBeginOverlap);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADZAnomalyCharacterBase::OnTriggerEndOverlap);
	}
	else
	{
		// 어빌리티 즉시 실행, 트리거 박스 콜리전 해제
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InASC->TryActivateAbility(AnomalyAbilitySpecHandle);
	}
}

void ADZAnomalyCharacterBase::OnRep_AnomalyScale()
{
	SetActorScale3D(FVector(ReplicatedAnomalyScale));
}
#pragma endregion
//======================================================================================================================		
#pragma region Cue Visual Interface

	//──────────────
	// Cue Visual Interface
	//──────────────	

bool ADZAnomalyCharacterBase::GetNiagaraCueData(const FGameplayTag& GATag, TArray<FDZNiagaraCueData>& OutData)
{
	if (NiagaraMap.Find(GATag))
	{
		OutData = NiagaraMap[GATag].NiagaraCueDataArray;
		return true;
	}
	return false;
}

bool ADZAnomalyCharacterBase::GetDecalCueData(const FGameplayTag& GATag, TArray<FDZDecalCueData>& OutData)
{
	if (DecalMap.Find(GATag))
	{
		OutData = DecalMap[GATag].DecalCueDataArray;
		return true;
	}
	return false;
}

bool ADZAnomalyCharacterBase::GetMaterialCueData(const FGameplayTag& GATag, TArray<FDZMaterialCueData>& OutData)
{
	if (MaterialMap.Find(GATag))
	{
		OutData = MaterialMap[GATag].MaterialCueDataArray;
		return true;
	}
	return false;
}

void ADZAnomalyCharacterBase::SetRecieveDecals(bool bEnable)
{
	// 컴포넌트의 리시브 데칼 변경
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);
	for (auto& PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->bReceivesDecals = bEnable;
		PrimitiveComponent->MarkRenderStateDirty();
	}
}
#pragma endregion
//======================================================================================================================	
#pragma region 트리거

//──────────────
// 트리거
//──────────────	

void ADZAnomalyCharacterBase::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor) || !OtherActor->IsA<ADZPlayerCharacter>())
	{
		return;
	}
	OverlappingPlayers++;
	// 플레이어 처음 들어왔을 때 어빌리티 실행
	if (OverlappingPlayers == 1)
	{
		AnomalyAbilitySystemComponent->TryActivateAbility(AnomalyAbilitySpecHandle);
	}
}

void ADZAnomalyCharacterBase::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->IsA<ADZPlayerCharacter>())
	{
		return;
	}
	if (!bDeactivateOnTrigger)
	{
		return;
	}
	OverlappingPlayers = FMath::Max(0, OverlappingPlayers - 1);
	// 플레이어 다 나갔을 때 어빌리티 취소
	if (OverlappingPlayers == 0)
	{
		AnomalyAbilitySystemComponent->CancelAbilityHandle(AnomalyAbilitySpecHandle);
	}
}

void ADZAnomalyCharacterBase::OnHitGround_Internal(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

#pragma endregion
//======================================================================================================================		
