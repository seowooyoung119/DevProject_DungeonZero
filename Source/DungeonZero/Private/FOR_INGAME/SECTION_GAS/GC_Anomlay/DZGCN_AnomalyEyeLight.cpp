// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyEyeLight.h"
#include "FOR_LIBRARY/Attach/DZAttachUtilLibrary.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZGCN_AnomalyEyeLight::ADZGCN_AnomalyEyeLight()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false; // 시작 시엔 Tick을 꺼둠 (최적화)
	
	bReplicates = true;
	bAutoDestroyOnRemove = true; 

	// 1. 가상의 루트를 생성하고 설정
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	// 2. 눈알 메시는 루트 밑에 부착
	Eye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eye"));
	Eye->SetupAttachment(SceneRoot);
	Eye->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// 감지 볼륨 설정
	DetectVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectVolume"));
	DetectVolume->SetupAttachment(RootComponent);
	DetectVolume->SetCollisionProfileName(TEXT("Trigger")); // 트리거 설정
	
}

bool ADZGCN_AnomalyEyeLight::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// 부모 및 컴포넌트 체크
	Super::OnActive_Implementation(MyTarget, Parameters);
	
	// 타겟 및 설정 체크
	UStaticMeshComponent* TargetMesh = UDZAttachUtilLibrary::GetStaticMeshComponentByMeshTag(MyTarget, EyeLightTargetMeshTag);
	if (!IsValid(TargetMesh))
	{
		if (HasAuthority()) UE_LOG(LogTemp, Warning, TEXT("호스트: 타겟 및 설정 체크"))
		else UE_LOG(LogTemp, Warning, TEXT("클라이언트: 타겟 및 설정 체크"));
		return false;
	}
	// 부착 
	bool bAttachIsSuccess = AttachToComponent(TargetMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocketName);
    if (!bAttachIsSuccess)
    {
    	if (HasAuthority()) UE_LOG(LogTemp, Warning, TEXT("호스트 : 부착"))
    	else UE_LOG(LogTemp, Warning, TEXT("클라이언트 : 부착"));
	    return false;
    }
	// 후 보정
	SetActorRelativeLocation(FVector::ZeroVector);
	SetActorRelativeRotation(FRotator::ZeroRotator);
	Eye->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
	DetectVolume->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
	
	// 트리거 바인딩
	DetectVolume->OnComponentBeginOverlap.AddDynamic(this, &ADZGCN_AnomalyEyeLight::OnOverlapBegin);
	DetectVolume->OnComponentEndOverlap.AddDynamic(this, &ADZGCN_AnomalyEyeLight::OnOverlapEnd);
	
	// 연출 시작 (현재 없음)
	
	if (HasAuthority()) UE_LOG(LogTemp, Warning, TEXT("호스트"))
	else UE_LOG(LogTemp, Warning, TEXT("클라이언트"));
	
	
	return true;	
}

void ADZGCN_AnomalyEyeLight::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (IsValid(TrackedPlayer) && IsValid(Eye))
	{
		// 소켓에 붙은 SceneRoot의 현재 월드 위치를 기준으로 계산
		FVector EyeLocation = Eye->GetComponentLocation();
		FVector TargetLocation = TrackedPlayer->GetPawnViewLocation(); 

		// 바라볼 방향 계산
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(EyeLocation, TargetLocation);

		// [중요] Eye 메시만 월드 회전값을 업데이트
		// 부모(소켓)가 어떻게 회전되어 있든 상관없이 월드 기준으로 플레이어를 쳐다봅니다.
		FRotator CurrentRot = Eye->GetComponentRotation();
		FRotator SmoothedRot = FMath::RInterpTo(CurrentRot, LookAtRot, DeltaSeconds, RotationInterpolationSpeed);
        
		Eye->SetWorldRotation(SmoothedRot);
	}
}

bool ADZGCN_AnomalyEyeLight::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// 연출 끝 (현재 없음)
	
	// 부착 해제
	if (IsValid(GetAttachParentActor())) DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
	// 트리거 바인딩 해제 
	DetectVolume->OnComponentBeginOverlap.RemoveAll(this);
	DetectVolume->OnComponentEndOverlap.RemoveAll(this);
	
	return Super::OnRemove_Implementation(MyTarget, Parameters);
}

#pragma endregion
//======================================================================================================================	
#pragma region 눈알

	//━━━━━━━━━━━━━━━━━━━━
	// 눈알
	//━━━━━━━━━━━━━━━━━━━━	

void ADZGCN_AnomalyEyeLight::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OverlappedPawn = Cast<APawn>(OtherActor);
	if (IsValid(OverlappedPawn) && OverlappedPawn->IsLocallyControlled())
	{
		TrackedPlayer = OverlappedPawn;
		SetActorTickEnabled(true); // 로컬 플레이어 진입 시 Tick 활성화
	}
}

void ADZGCN_AnomalyEyeLight::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == TrackedPlayer)
	{
		TrackedPlayer = nullptr;
		SetActorTickEnabled(false); // 로컬 플레이어 이탈 시 Tick 비활성화
	}
}


#pragma endregion
//======================================================================================================================	