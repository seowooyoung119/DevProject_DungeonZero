// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Stage/DZAllowPlayerControlMSG.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZInGameOverlay.generated.h"

class UBorder;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInGameOverlay : public UUserWidget
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클 
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
#pragma endregion
//=====================================================================================================================
#pragma region 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBorder> FadeInoutOBorder = nullptr;
	
#pragma endregion
//======================================================================================================================	
#pragma region StageAPI	
	
	//━━━━━━━━━━━━━━━━━━━━
	// StageAPI
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	// 메시지 수신 함수
	void OnCanMoveAndSeeReceived(FGameplayTag Channel, const FDZAllowPlayerControlMSG& Payload);	

	// 실제 실행 함수
	UFUNCTION(BlueprintImplementableEvent)
	void StartFadeInAndOut(bool bCanMoveAndSee);
	
	// 구독 핸들
	FGameplayMessageListenerHandle CanMoveAndSeeListenerHandle;
	
#pragma endregion
//======================================================================================================================		
};
