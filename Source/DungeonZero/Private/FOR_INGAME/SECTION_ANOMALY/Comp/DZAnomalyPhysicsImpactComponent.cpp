// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Comp/DZAnomalyPhysicsImpactComponent.h"

#include "FOR_INGAME/SECTION_ANOMALY/Actor/Base/DZAnomalyActorBase.h"
#include "AbilitySystemComponent.h"
#include "FOR_COMMON/SECTION_TAG/GAS/GameplayCue/DZGameplayCueTag.h"
#include "FOR_COMMON/SECTION_TAG/GAS/Status/DZAnomalyStatus.h"
#include "FOR_INGAME/SECTION_GAS/Data/Struct/DZPhysicsImpactData.h"
#include "FOR_LIBRARY/LineTarce/DZSurfaceTraceHelperLibrary.h"
#include "FOR_INGAME/SECTION_SOUND/FootStep/Data/Asset/DZAnomalySoundDataAsset.h"


UDZAnomalyPhysicsImpactComponent::UDZAnomalyPhysicsImpactComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDZAnomalyPhysicsImpactComponent::BeginPlay()
{
	Super::BeginPlay();

	// 오너 액터(어노말리 액터) 가져오기
	ADZAnomalyActorBase* AnomalyActor = Cast<ADZAnomalyActorBase>(GetOwner());
	if (!IsValid(AnomalyActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("AnomalyActor is not valid"));
		return;
	}
	// 오너 액터 ASC 가져오기
	OwnerASC = AnomalyActor->GetAbilitySystemComponent();
	if (!IsValid(OwnerASC))
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerASC  is not valid"));
		return;
	}
	// 오너 액터 컴포넌트 가져오기
	OwnerPrimitiveComponent = AnomalyActor->GetAnomalyPrimitiveComponent();
	if (!IsValid(OwnerPrimitiveComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerPrimitiveComponent is not valid"));
		return;
	}
}

bool UDZAnomalyPhysicsImpactComponent::GetPhysicsImpactData(const FGameplayTag& GATag, FDZPhysicsImpactData& OutData)
{
	// 어빌리티 태그에 매핑된 데이터 출력
	if (ImpactDataMap.Find(GATag))
	{
		OutData = ImpactDataMap[GATag];
		return true;
	}
	return false;
}

TObjectPtr<USoundBase> UDZAnomalyPhysicsImpactComponent::GetImpactSound(const FHitResult& Hit)
{
	TObjectPtr<USoundBase> Sound = nullptr;
	if (!IsValid(ImpactSoundDataAsset))
	{
		return Sound;
	}

	// 표면 타입 검출
	if (!Hit.IsValidBlockingHit())
	{
		return Sound;
	}

	// 라이브러리 호출
	EPhysicalSurface SurfaceType = UDZSurfaceTraceHelperLibrary::GetSurfaceTypeFromHit(Hit);

	// 타입에 매핑된 사운드 출력
	Sound = ImpactSoundDataAsset->AnomalySounds.FindRef(SurfaceType);
	if (!Sound)
	{
		// 매핑된 사운드 없으면 디폴트 사운드
		Sound = ImpactSoundDataAsset->DefaultSound;
	}
	return Sound;
}

void UDZAnomalyPhysicsImpactComponent::ActivatePhysics_internal(FGameplayTagContainer InAbilityTags)
{
	// 바인딩 여부 체크
	if (OwnerPrimitiveComponent->OnComponentHit.IsAlreadyBound(
		this, &UDZAnomalyPhysicsImpactComponent::OnHitGround_internal))
	{
		return;
	}

	// 어빌리티 태그 저장
	PendingAbilityTags = InAbilityTags;
	// 피직스 활성화
	OwnerPrimitiveComponent->SetIsReplicated(true);
	OwnerPrimitiveComponent->SetSimulatePhysics(true);
	OwnerPrimitiveComponent->SetNotifyRigidBodyCollision(true);
	// 빠른 오브젝트가 벽 통과하지 않도록 CCD 활성화
	OwnerPrimitiveComponent->BodyInstance.SetUseCCD(true);
	// Hit 이벤트 바인딩
	OwnerPrimitiveComponent->OnComponentHit.AddDynamic(this, &UDZAnomalyPhysicsImpactComponent::OnHitGround_internal);
}

void UDZAnomalyPhysicsImpactComponent::OnHitGround_internal(UPrimitiveComponent* HitComp, AActor* OtherActor,
                                                            UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                                            const FHitResult& Hit)
{
	// 서버에서만 실행
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	// 메시가 착지한 위치로 액터(Root) 위치 동기화
	FVector MeshWorldLocation = OwnerPrimitiveComponent->GetComponentLocation();
	if (GetOwner())
	{
		GetOwner()->SetActorLocation(MeshWorldLocation);
		GetOwner()->UpdateOverlaps();
	}
	// 1. 임팩트 조건
	if (HitComp->GetComponentVelocity().Size() > 100.0f)
	{
		FGameplayEffectContextHandle ContextHandle = OwnerASC->MakeEffectContext();
		ContextHandle.AddHitResult(Hit);

		FGameplayCueParameters CueParams;
		CueParams.AggregatedSourceTags.AppendTags(PendingAbilityTags);
		CueParams.EffectContext = ContextHandle;
		// 사운드 큐 실행
		OwnerASC->ExecuteGameplayCue(DZ::GameplayCue::DZ_CUE_ANOMALY_IMPACTSOUND, CueParams);
	}

	// 2. 종료 조건
	if (HitComp->GetComponentVelocity().Size() < 10.0f)
	{
		FinishPhysicsImpact();
	}
}

void UDZAnomalyPhysicsImpactComponent::FinishPhysicsImpact()
{
	// 완전히 멈췄을 때 피직스 비활성화 및 바인딩 해제
	OwnerPrimitiveComponent->SetSimulatePhysics(false);
	OwnerPrimitiveComponent->OnComponentHit.RemoveAll(this);
	// CCD 비활성화
	OwnerPrimitiveComponent->BodyInstance.SetUseCCD(false);
}
