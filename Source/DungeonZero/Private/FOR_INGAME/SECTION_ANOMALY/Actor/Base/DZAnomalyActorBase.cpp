// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
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

ADZAnomalyActorBase::ADZAnomalyActorBase()
{
	// tick
	PrimaryActorTick.bCanEverTick = false;

	// rep
	bReplicates = true;
	SetReplicatingMovement(true);
	
	AnomalyAbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(
		TEXT("AnomalyAbilitySystemComponent"));
	AnomalyAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

void ADZAnomalyActorBase::BeginPlay()
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

void ADZAnomalyActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
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

void ADZAnomalyActorBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADZAnomalyActorBase, ReplicatedAnomalyScale);
}

void ADZAnomalyActorBase::SetAnomalyScale(float InScale)
{
	ReplicatedAnomalyScale = InScale;
	SetActorScale3D(FVector(InScale));
}

void ADZAnomalyActorBase::InitGAS_internal(UAbilitySystemComponent* InASC)
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
	// 어빌리티 부여
	FGameplayAbilitySpec AbilitySpec(SelectedData.GameplayAbility, 1, INDEX_NONE,
	                                 this);
	AnomalyAbilitySpecHandle = InASC->GiveAbility(AbilitySpec);
}

void ADZAnomalyActorBase::ActivateAnomaly_internal(UAbilitySystemComponent* InASC)
{
	if (!IsValid(InASC) || !AnomalyAbilitySpecHandle.IsValid())
	{
		return;
	}
	if (bActivateOnTrigger)
	{
		// 오버랩 바인딩
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADZAnomalyActorBase::OnTriggerBeginOverlap);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADZAnomalyActorBase::OnTriggerEndOverlap);
	}
	else
	{
		// 어빌리티 즉시 실행, 트리거 박스 콜리전 해제
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InASC->TryActivateAbility(AnomalyAbilitySpecHandle);
	}
}

void ADZAnomalyActorBase::OnRep_AnomalyScale()
{
	SetActorScale3D(FVector(ReplicatedAnomalyScale));
}
#pragma endregion
//======================================================================================================================		
#pragma region Cue Visual Interface

//──────────────
// Cue Visual Interface
//──────────────	
bool ADZAnomalyActorBase::GetNiagaraCueData(const FGameplayTag& GATag, TArray<FDZNiagaraCueData>& OutData)
{
	if (NiagaraMap.Find(GATag))
	{
		OutData = NiagaraMap[GATag].NiagaraCueDataArray;
		return true;
	}
	return false;
}

bool ADZAnomalyActorBase::GetDecalCueData(const FGameplayTag& GATag, TArray<FDZDecalCueData>& OutData)
{
	if (DecalMap.Find(GATag))
	{
		OutData = DecalMap[GATag].DecalCueDataArray;
		return true;
	}
	return false;
}

bool ADZAnomalyActorBase::GetMaterialCueData(const FGameplayTag& GATag, TArray<FDZMaterialCueData>& OutData)
{
	if (MaterialMap.Find(GATag))
	{
		OutData = MaterialMap[GATag].MaterialCueDataArray;
		return true;
	}
	return false;
}

void ADZAnomalyActorBase::SetRecieveDecals(bool bEnable)
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

void ADZAnomalyActorBase::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult& SweepResult)
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

void ADZAnomalyActorBase::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsValid(OtherActor) || !OtherActor->IsA<ADZPlayerCharacter>())
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

void ADZAnomalyActorBase::OnHitGround_Internal(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

#pragma endregion
//======================================================================================================================		
