// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_INTERACT/Interface/DZCommonInteractInterface.h"
#include "GameFramework/Actor.h"
#include "DZCampfireActor.generated.h"

class UAudioComponent;
class UNiagaraComponent;
class UWidgetComponent;
class ADZTorchLight;

UCLASS()
class DUNGEONZERO_API ADZCampfireActor : public AActor, public IDZCommonInteractInterface
{
	GENERATED_BODY()
//======================================================================================================================
#pragma region 라이프_사이클

    //━━━━━━━━━━━━━━━━━━━━
    // 라이프 사이클
    //━━━━━━━━━━━━━━━━━━━━
public:
    ADZCampfireActor();
    virtual void BeginPlay() override;

#pragma endregion
//======================================================================================================================
#pragma region 컴포넌트

    //━━━━━━━━━━━━━━━━━━━━
    // 컴포넌트
    //━━━━━━━━━━━━━━━━━━━━
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Campfire")
    TObjectPtr<UStaticMeshComponent> CampfireMeshComp = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Campfire")
    TObjectPtr<UAudioComponent> Audio = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Campfire")
    TObjectPtr<UNiagaraComponent> Niagara = nullptr;

#pragma endregion
//======================================================================================================================
#pragma region 인터렉트_섹션

    //━━━━━━━━━━━━━━━━━━━━
    // 인터렉트 섹션
    //━━━━━━━━━━━━━━━━━━━━
public:
    // IDZCommonInteractInterface ~
    virtual void ToggleInteractWidget_Implementation(bool InWantOn) override;
    virtual void DoStandAloneInteractLogic_Implementation(FDZInteractData& InteractData) override;
    // ~ IDZCommonInteractInterface

#pragma endregion
//======================================================================================================================
};
