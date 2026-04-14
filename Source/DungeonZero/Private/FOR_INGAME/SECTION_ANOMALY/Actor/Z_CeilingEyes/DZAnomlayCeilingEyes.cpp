// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ANOMALY/Actor/Z_CeilingEyes/DZAnomlayCeilingEyes.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━		

ADZAnomalyCeilingEyes::ADZAnomalyCeilingEyes()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false; // 시작 시엔 Tick을 꺼둠 (최적화)
	
	DetectVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectVolume"));
	RootComponent = DetectVolume;
}

void ADZAnomalyCeilingEyes::BeginPlay()
{
	Super::BeginPlay();
	
	// 트리거 바인딩
	if (IsValid(DetectVolume))
	{
		DetectVolume->OnComponentBeginOverlap.AddDynamic(this, &ADZAnomalyCeilingEyes::OnOverlapBegin);
		DetectVolume->OnComponentEndOverlap.AddDynamic(this, &ADZAnomalyCeilingEyes::OnOverlapEnd);
	}

	// 1. 에디터에서 배치한 EyeComponents를 기반으로 런타임 데이터 캐싱
	EyeInstances.Empty();
	for (UStaticMeshComponent* Mesh : EyeComponents)
	{
		if (IsValid(Mesh))
		{
			FEyeInstanceData NewData;
			NewData.MeshComponent = Mesh;
			// 랜덤한 회전 속도 부여
			NewData.IndividualSpeed = FMath::FRandRange(MinRotationSpeed, MaxRotationSpeed);
			EyeInstances.Add(NewData);
		}
	}
}

void ADZAnomalyCeilingEyes::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// TrackedPlayer가 유효한지 한 번 더 체크
	if (IsValid(TrackedPlayer) && EyeInstances.Num() > 0)
	{
		FVector TargetLocation = TrackedPlayer->GetActorLocation();

		for (auto& Eye : EyeInstances)
		{
			if (!IsValid(Eye.MeshComponent)) continue;

			// 1. 순수하게 타겟을 향한 월드 기준 회전값을 구합니다.
			FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			   Eye.MeshComponent->GetComponentLocation(), 
			   TargetLocation
			);
            
			// 2. [핵심] 단순 + 가 아니라 Compose를 사용합니다.
			// EyeRotationOffset(메쉬의 앞방향 보정)을 먼저 적용하고, 그 다음 LookAt 회전을 입힙니다.
			FRotator FinalTargetRot = UKismetMathLibrary::ComposeRotators(EyeRotationOffset, LookAtRot);
          
			// 3. 보간 (Interp)
			FRotator CurrentRot = Eye.MeshComponent->GetComponentRotation();
          
			// 쿼터니언 보간을 사용하면 짐벌락(회전 꼬임) 현상을 더 완벽하게 방지할 수 있습니다.
			FRotator NewRot = FMath::RInterpTo(CurrentRot, FinalTargetRot, DeltaSeconds, Eye.IndividualSpeed);

			Eye.MeshComponent->SetWorldRotation(NewRot);
		}
	}
}
	
#pragma endregion
//======================================================================================================================	
#pragma region 눈알

	//━━━━━━━━━━━━━━━━━━━━
	// 눈알
	//━━━━━━━━━━━━━━━━━━━━	

void ADZAnomalyCeilingEyes::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OverlappedPawn = Cast<APawn>(OtherActor);
	if (IsValid(OverlappedPawn) && OverlappedPawn->IsPlayerControlled())
	{
		TrackedPlayer = OverlappedPawn;
		SetActorTickEnabled(true); // 추적 시작
	}
}

void ADZAnomalyCeilingEyes::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == TrackedPlayer)
	{
		TrackedPlayer = nullptr;
		SetActorTickEnabled(false); // 추적 중지 (최적화)
	}
}

#pragma endregion
//======================================================================================================================	