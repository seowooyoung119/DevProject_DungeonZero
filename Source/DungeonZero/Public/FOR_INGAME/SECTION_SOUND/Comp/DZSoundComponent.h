// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DZSoundComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDZSoundComponent();

protected:
	// Default Attenuation
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundAttenuation> DefaultAttenuation = nullptr;
	
	// 아래 방향 표면 타입 검출
	UFUNCTION(BlueprintCallable, Category = "Sound")
	EPhysicalSurface GetSurfaceTypeBelow(const FVector& Location, float TraceLength = 50.f) const;

	// 앞 방향 표면 타입 검출
	UFUNCTION(BlueprintCallable, Category = "Sound")
	EPhysicalSurface GetSurfaceTypeFront(const FVector& Location, const FVector& ForwardVector, float TraceLength = 100.f) const;
	
	// HitResult에서 표면 타입 검출
	UFUNCTION(BlueprintCallable, Category = "Sound")
	EPhysicalSurface GetSurfaceTypeFromHit(const FHitResult& Hit) const;
	
	bool LineTrace(const FVector& Start, const FVector& End, FHitResult& OutHit) const;
	void PlaySoundAtLocation(USoundBase* Sound, const FVector& Location) const;
};
