// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_SOUND/FootStep/A_Base/DZFootStepSoundMasterComponent.h"
#include "FOR_INGAME/SECTION_SOUND/FootStep/Data/Asset/DZFootStepSoundDataAsset.h"
#include "FOR_LIBRARY/LineTarce/DZSurfaceTraceHelperLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━		

UDZFootStepSoundMasterComponent::UDZFootStepSoundMasterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDZFootStepSoundMasterComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetOwner()))
	{
		return;
	}
	OwnerCharacter = CastChecked<ACharacter>(GetOwner());
	OwnerCharacter->LandedDelegate.AddDynamic(this, &UDZFootStepSoundMasterComponent::OnLanded);
}

#pragma endregion
//======================================================================================================================	
#pragma region 풋스텝

	//━━━━━━━━━━━━━━━━━━━━
	// 풋스텝
	//━━━━━━━━━━━━━━━━━━━━	

void UDZFootStepSoundMasterComponent::PlayFootstepSound(const FVector& Location, const bool bIsLeft)
{
	if (!IsValid(FootStepSoundDataAsset))
	{
		return;
	}
	
	// 라이브러리 호출로 표면 타입 검출
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	EPhysicalSurface SurfaceType = UDZSurfaceTraceHelperLibrary::GetSurfaceTypeBelow(this, Location, 50.f,CollisionQueryParams,HitResult);
	
	// 타입에 매핑된 사운드 출력
	const auto* Sounds = FootStepSoundDataAsset->FootstepSounds.Find(SurfaceType);
	if (!Sounds)
	{
		// 매핑된 사운드 없으면 디폴트 사운드
		Sounds = &FootStepSoundDataAsset->DefaultFootstepSound;
	}
	
	// 왼발
	USoundBase* Sound = Sounds->FootStep_Right;

	// 오른발
	if (bIsLeft)
	{
		Sound = Sounds->FootStep_Left;
	}

	// 사운드 재생
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location,FRotator::ZeroRotator,1.f, 1.f, 0.f,FootStepSoundDataAsset->DefaultAttenuation);
}

void UDZFootStepSoundMasterComponent::OnLanded(const FHitResult& Hit)
{
	if (!IsValid(FootStepSoundDataAsset))
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
	
	// 타입에 매핑된 사운드 출력
	const auto* Sounds = FootStepSoundDataAsset->FootstepSounds.Find(SurfaceType);
	if (!Sounds)
	{
		// 매핑된 사운드 없으면 디폴트 사운드
		Sounds = &FootStepSoundDataAsset->DefaultFootstepSound;
	}

	// 사운드 재생
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sounds->FootStep_Left, Hit.ImpactPoint,FRotator::ZeroRotator,1.f, 1.f, 0.f,FootStepSoundDataAsset->DefaultAttenuation);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sounds->FootStep_Right, Hit.ImpactPoint,FRotator::ZeroRotator,1.f, 1.f, 0.f,FootStepSoundDataAsset->DefaultAttenuation);

}

#pragma endregion
//======================================================================================================================	
