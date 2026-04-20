// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_VFX/FootStep/A_Base/DZFootStepVFXMasterComponent.h"
#include "FOR_INGAME/SECTION_VFX/FootStep/Data/Asset/DZFootStepVFXDataAsset.h"
#include "FOR_LIBRARY/LineTarce/DZSurfaceTraceHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━		

UDZFootStepVFXMasterComponent::UDZFootStepVFXMasterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDZFootStepVFXMasterComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetOwner()))
	{
		return;
	}
	OwnerCharacter = CastChecked<ACharacter>(GetOwner());
	OwnerCharacter->LandedDelegate.AddDynamic(this, &UDZFootStepVFXMasterComponent::OnLandedVFX);
}

#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	

void UDZFootStepVFXMasterComponent::PlayFootstepVFX(const FVector& SocketLocation, const FRotator& SocketRotation, bool& bIsLeft)
{
	if (!IsValid(FootStepVfxDataAsset))
	{
		return;
	}
	
	// 라이브러리 호출로 표면 타입 검출
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	EPhysicalSurface SurfaceType = UDZSurfaceTraceHelperLibrary::GetSurfaceTypeBelow(this, SocketLocation, 50.f,CollisionQueryParams, HitResult);
	
	// 타입에 매핑된 vfx 출력
	const FDZFootstepVFXData* VfxData = FootStepVfxDataAsset->SurfaceVFXMap.Find(SurfaceType);
	if (!VfxData)
	{
		// 없으면 디폴트 
		VfxData = &FootStepVfxDataAsset->DefaultVFXData;
	}
	
	SpawnVFXAndDecal(SocketLocation, SocketRotation, *VfxData, HitResult, bIsLeft);
}

void UDZFootStepVFXMasterComponent::OnLandedVFX(const FHitResult& Hit)
{
	if (!IsValid(FootStepVfxDataAsset))
	{
		return;
	}
	
	// 표면 타입 검출
	if (!Hit.IsValidBlockingHit())
	{
		return;
	}
	
	// 라이브러리 호출
	EPhysicalSurface SurfaceType = UDZSurfaceTraceHelperLibrary::GetSurfaceTypeFromHit(Hit);
	
	// 타입에 매핑된 vfx 출력
	const FDZFootstepVFXData* VfxData = FootStepVfxDataAsset->SurfaceVFXMap.Find(SurfaceType);
	if (!VfxData)
	{
		// 없으면 디폴트 
		VfxData = &FootStepVfxDataAsset->DefaultVFXData;
	}

	//=====================================
	// 착지 시 무언가는 아직 미정 
	//=====================================
}

void UDZFootStepVFXMasterComponent::SpawnVFXAndDecal(const FVector& SocketLocation, const FRotator& SocketRotation, const FDZFootstepVFXData& Data, const FHitResult& Hit, bool bIsLeft)
{
	if (!IsValid(OwnerCharacter))
	{
		OwnerCharacter = CastChecked<ACharacter>(GetOwner());
		return;
	}
		
	// 1. 나이아가라 파티클 생성
	if (IsValid(Data.FootstepParticle))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Data.FootstepParticle, Hit.ImpactPoint, SocketRotation);
	}
	
	// 2. 현재 발에 맞는 데이터 선택
	UMaterialInterface* TargetMaterial = bIsLeft ? Data.LeftFootstepDecal.Get() : Data.RightFootstepDecal.Get();
	float FoundDecalRotation = bIsLeft ? Data.DecalRotation_Left : Data.DecalRotation_Right;
	if (!IsValid(TargetMaterial))
	{
		return;
	}
	
	// 데칼의 X축은 바닥(-Normal)을 향하고, 데칼의 상단 방향은 소켓의 Forward(또는 캐릭터 진행방향)와 정렬.
	FVector ProjectionDir = -Hit.ImpactNormal;															// 바닥으로 쏘는 방향
	FVector FootForward = UKismetMathLibrary::GetForwardVector(OwnerCharacter->GetActorRotation());// 발가락 방향

	// 바닥 면(Normal)에 수직인 새로운 회전값 생성
	// MakeRotFromXZ: X는 바닥을 뚫고 들어가는 방향, Z는 발가락이 가리키는 방향
	FRotator FinalDecalRotation = UKismetMathLibrary::MakeRotFromXZ(ProjectionDir, FootForward);
		
	// 발자국 텍스처가 기본적으로 회전 보정
	FinalDecalRotation = UKismetMathLibrary::ComposeRotators(FRotator(0, 0, FoundDecalRotation), FinalDecalRotation);

	// 3. 데칼 스폰
	UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), TargetMaterial, Data.DecalSize, Hit.ImpactPoint, FinalDecalRotation, Data.DecalLifeSpan);
	if (!IsValid(DecalComp))
	{
		return;
	}
	
	// 4. 다이내믹 머티리얼 생성 및 파라미터 전달
	UMaterialInstanceDynamic* DynamicMat = DecalComp->CreateDynamicMaterialInstance();
	if (!IsValid(DynamicMat))
	{
		return;
	}
	
	// 현재 게임 시간을 SpawnTime으로 전달
	DynamicMat->SetScalarParameterValue(TEXT("SpawnTime"), GetWorld()->GetTimeSeconds());
	// 사라지는 총 시간(LifeSpan) 전달
	DynamicMat->SetScalarParameterValue(TEXT("LifeSpan"), Data.DecalLifeSpan);
	
	FootPrints.Add(DecalComp);
}


#pragma endregion
//======================================================================================================================	
