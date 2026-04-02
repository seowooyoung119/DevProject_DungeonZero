// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_GAS/GC_Anomlay/DZGCN_AnomalyEyeLight.h"
#include "FOR_LIBRARY/Attach/DZAttachUtilLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"
#include "NiagaraComponent.h"

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

ADZGCN_AnomalyEyeLight::ADZGCN_AnomalyEyeLight()
{
	bReplicates = true;
	
	bAutoDestroyOnRemove = true; 

	EyeLightRoot = CreateDefaultSubobject<USceneComponent>(TEXT("EyeLightRoot"));
	SetRootComponent(EyeLightRoot);
	
	EyeLightVFXEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EyeLightVFXEffect"));
	EyeLightVFXEffect->SetupAttachment(GetRootComponent());
	EyeLightVFXEffect->SetAutoActivate(false);

	EyeLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("EyeLightComponent"));
	EyeLightComponent->SetupAttachment(EyeLightRoot);
	EyeLightComponent->SetAutoActivate(false);
	
	EyeSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EyeSoundComponent"));
	EyeSoundComponent->SetupAttachment(EyeLightRoot);
	EyeSoundComponent->SetAutoActivate(false);
	
}

bool ADZGCN_AnomalyEyeLight::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// 부모 및 컴포넌트 체크
	Super::OnActive_Implementation(MyTarget, Parameters);
	if (!IsValid(EyeLightRoot))  return false;
	if (!IsValid(EyeLightVFXEffect)) return false;
	if (!IsValid(EyeLightComponent)) return false;
	if (!IsValid(EyeSoundComponent))  return false;
	
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
	
	// 연출 시작
	EyeLightVFXEffect->Activate();
	EyeLightComponent->Activate();
	EyeSoundComponent->Activate();
	EyeSoundComponent->Play();

	
	if (HasAuthority()) UE_LOG(LogTemp, Warning, TEXT("호스트"))
	else UE_LOG(LogTemp, Warning, TEXT("클라이언트"));
	
	
	return true;	
}

bool ADZGCN_AnomalyEyeLight::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// 연출 끝
	if (IsValid(EyeLightVFXEffect) )EyeLightVFXEffect->Deactivate();
	if (IsValid(EyeLightComponent)) EyeLightComponent->Deactivate();
	if (IsValid(EyeSoundComponent))
	{
		EyeSoundComponent->Deactivate();
		EyeSoundComponent->Stop();
	}
	
	// 부착 해제
	if (IsValid(GetAttachParentActor())) DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
	return Super::OnRemove_Implementation(MyTarget, Parameters);
}

#pragma endregion
//======================================================================================================================	