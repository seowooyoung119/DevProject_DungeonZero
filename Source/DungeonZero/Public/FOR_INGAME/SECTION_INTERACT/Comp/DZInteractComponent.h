// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZInteractComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZInteractComponent : public UActorComponent
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	UDZInteractComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
#pragma endregion 
//======================================================================================================================	
#pragma region 인터렉트_내부_동작_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트 내부 동작 API
	//━━━━━━━━━━━━━━━━━━━━
	
protected:

	// 인터렉트 tick 총괄 함수 
	void TickInteract_internal();
	
	// 선행 1 : 오너 플레이어 컨트롤러 캐싱 확인 함수 
	bool HasCachingOwnerPlayerController_internal();
	
	// 선행 2: 라인 트레이스 실시 함수 
	AActor* LineTrace_internal();
	
	// 선행 3: 후 처리 함수
	void DoInteractUILogicAfterLineTrace();
	
	
#pragma endregion
//======================================================================================================================	
#pragma region 인터렉트_데이터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_데이터
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// 현재 액터와 지난 액터 Getter
	FORCEINLINE AActor* GetCurrentInteractActor() const { return IsValid(CurrentInteractActor) ? CurrentInteractActor : nullptr; }
	FORCEINLINE AActor* GetLastInteractActor() const { return IsValid(LastInteractActor )? LastInteractActor : nullptr; }
	
protected:

	// 상호작용 가능한 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Interact")
	float InteractDistance = 500.0f;
	
	// 캐싱한 플레이어 컨트롤러 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Interact")
	TObjectPtr<APlayerController> OwnerPlayerController = nullptr;
	
	// 현재 보는 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Interact")
	TObjectPtr<AActor> CurrentInteractActor = nullptr;

	// 마지막으로 본 액터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Interact")
	TObjectPtr<AActor> LastInteractActor = nullptr;

	// 디버그
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Interact")
	bool bDebugDrawLine = false;
	
#pragma endregion 
//======================================================================================================================
};
