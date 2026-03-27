// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "DZInputHandleComponent.generated.h"


class UDZInputDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZInputHandleComponent : public UActorComponent
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	UDZInputHandleComponent();

#pragma endregion
//======================================================================================================================	
#pragma region 외부_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 외부_API
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// 캐릭터로부터 호출받아 입력을 바인딩할 함수
	void SetupInput(UEnhancedInputComponent* InEnhancedInputComponent);

protected:
	// 플레이어 캐릭터 캐싱 
	bool CachingCharacterAndController_internal();
	
#pragma endregion
//======================================================================================================================	
#pragma region 움직임_관련
	
	//━━━━━━━━━━━━━━━━━━━━
	// 움직임_관련
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	// 실제 이동 로직 (Callback)
	void Move_internal(const FInputActionValue& Value);
	void Look_internal(const FInputActionValue& Value);
	void Jump_internal(const FInputActionValue& Value);
	
#pragma endregion
//======================================================================================================================	
#pragma region 상호작용_관련
	
	//━━━━━━━━━━━━━━━━━━━━
	// 상호작용_관련
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	void InteractByLeftClick_internal(const FInputActionValue& Value);
	
#pragma endregion
//======================================================================================================================	
#pragma region 데이터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 데이터
	//━━━━━━━━━━━━━━━━━━━━	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TS | Input")
	TObjectPtr<UDZInputDataAsset> InputData = nullptr;
	
	// 오너 캐릭터 캐싱 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;
	
	// 오너 컨트롤러 캐싱 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TS | Input")
	TObjectPtr<APlayerController> OwnerController = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
