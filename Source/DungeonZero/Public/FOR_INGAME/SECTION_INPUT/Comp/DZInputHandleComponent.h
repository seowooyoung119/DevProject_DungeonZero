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
	void Move_internal(const FInputActionValue& Value); // WASD 움직임
	void Look_internal(const FInputActionValue& Value);	// 시야 회전
	void Jump_internal(const FInputActionValue& Value); // 점프 
	void RunStart_internal(const FInputActionValue& Value);  // 달리기 시작
	void RunEnd_internal(const FInputActionValue& Value);	 // 달리기 끝
#pragma endregion
//======================================================================================================================	
#pragma region 상호작용_관련
	
	//━━━━━━━━━━━━━━━━━━━━
	// 상호작용_관련
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	void InteractByLeftClick_internal(const FInputActionValue& Value);	// 왼쪽 마우스 (사물 들어올리기)
	void InteractByRightClick_internal(const FInputActionValue& Value);	// 오른쪽 마우스 (아이템 사용)
	void SpecialInteract_internal(const FInputActionValue& Value);		// 특수 상호작용
	void PickUpItem_internal(const FInputActionValue& Value);			// 아이템 줍기
	void DropItem_internal(const FInputActionValue& Value);				// 아이템 버리기 
	
#pragma endregion
//======================================================================================================================	
#pragma region 핫키 
	
	//━━━━━━━━━━━━━━━━━━━━
	// 상호작용_관련
	//━━━━━━━━━━━━━━━━━━━━	

protected:
	void HotKey_internal1(const FInputActionValue& Value);
	void HotKey_internal2(const FInputActionValue& Value);
	void HotKey_internal3(const FInputActionValue& Value);
	void HotKey_internal4(const FInputActionValue& Value);
	void HotKey_internal5(const FInputActionValue& Value);
	void HotKey_internal6(const FInputActionValue& Value);
	void HotKey_internal7(const FInputActionValue& Value);
	void HotKey_internal8(const FInputActionValue& Value);
	void HotKey_internal9(const FInputActionValue& Value);

#pragma endregion
//======================================================================================================================	
#pragma region 내부유틸
	
	//━━━━━━━━━━━━━━━━━━━━
	// 내부유틸
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	bool HasPlayerDead();
	
#pragma endregion
//======================================================================================================================	
#pragma region 데이터
	
	//━━━━━━━━━━━━━━━━━━━━
	// 데이터
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Input")
	TObjectPtr<UDZInputDataAsset> InputData = nullptr;
	
	// 오너 캐릭터 캐싱 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Input")
	TObjectPtr<ACharacter> OwnerCharacter = nullptr;
	
	// 오너 컨트롤러 캐싱 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Input")
	TObjectPtr<APlayerController> OwnerController = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
