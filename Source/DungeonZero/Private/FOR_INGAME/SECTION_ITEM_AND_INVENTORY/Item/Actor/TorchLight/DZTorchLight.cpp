// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/TorchLight/DZTorchLight.h"

#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PointLightComponent.h"

ADZTorchLight::ADZTorchLight()
{
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	Audio->SetupAttachment(ItemStaticMeshComp);

	Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	Niagara->SetupAttachment(ItemStaticMeshComp);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(ItemStaticMeshComp);
}

void ADZTorchLight::BeginPlay()
{
	Super::BeginPlay();
	PointLight->SetIntensity(InitialIntensity);
	if (!IsValid(GetOwner()))
	{
		return;
	}
	// 오너 설정 되어있을 때만 Light Tick 타이머 설정
	StartLightDecreaseTimer();
}

void ADZTorchLight::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(LightDecreaseTimerHandle);
	Super::EndPlay(EndPlayReason);
}

void ADZTorchLight::LightDecreaseTick_internal()
{
	float NextIntensity = FMath::Max(0.f, PointLight->Intensity - IntensityDecreasePerTick);
	if (PointLight->Intensity > 0.f && NextIntensity == 0.f)
	{
		SetTorchActivated(false);
		return;
	}
	Niagara->SetVariableFloat(NiagaraParameterName, NextIntensity / InitialIntensity * NiagaraInitialFireScale);
	PointLight->SetIntensity(NextIntensity);
}

void ADZTorchLight::StartLightDecreaseTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(LightDecreaseTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		LightDecreaseTimerHandle,
		this,
		&ADZTorchLight::LightDecreaseTick_internal,
		1.0f,
		true
	);
}

void ADZTorchLight::TorchCharge_Implementation()
{
	SetTorchActivated(true);
}

void ADZTorchLight::SetTorchActivated(bool bIsActive)
{
	if (bIsActive)
	{
		PointLight->SetIntensity(InitialIntensity);
		Niagara->SetVariableFloat(NiagaraParameterName, NiagaraInitialFireScale);
		if (!Audio->IsPlaying())
		{
			Audio->Play();
		}
		// 타이머 시작
		StartLightDecreaseTimer();
	}
	else
	{
		// 타이머 해제
		GetWorld()->GetTimerManager().ClearTimer(LightDecreaseTimerHandle);
		PointLight->SetIntensity(0.f);
		Niagara->SetVariableFloat(NiagaraParameterName, 0.f);
		if (Audio->IsPlaying())
		{
			Audio->Stop();
		}
	}
}
