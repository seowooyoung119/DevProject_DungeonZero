// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FOR_INGAME/SECTION_INTERACT/Interface/DZCommonInteractInterface.h"
#include "DZLeverActor.generated.h"

class ADZDoorActor;
class UWidgetComponent;

UCLASS()
class DUNGEONZERO_API ADZLeverActor : public AActor, public IDZCommonInteractInterface
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZLeverActor();
	
#pragma endregion
//======================================================================================================================	
#pragma region 인터렉트_섹션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 인터렉트_섹션
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// IDZCommonInteractInterface ~ 
	virtual void ToggleInteractWidget_Implementation(bool InWantOn) override;
	virtual void DoStandAloneInteractLogic_Implementation() override;
	// ~ IDZCommonInteractInterface
	
protected:
	
	// 위젯 컴포넌트 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<UWidgetComponent> InteractWidgetComp = nullptr;
	
#pragma endregion
//======================================================================================================================
#pragma region 레버
	
	//━━━━━━━━━━━━━━━━━━━━
	// 레버
	//━━━━━━━━━━━━━━━━━━━━		

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<USceneComponent> LeverRoot = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	TObjectPtr<ADZDoorActor> TargetDoor = nullptr;
	
#pragma endregion
//======================================================================================================================	
};
