// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_COMMON/SECTION_PLAY_ROLE/Interface/DZCommonPlayRoleInterface.h"
#include "GameFramework/Actor.h"
#include "DZOriginActorBase.generated.h"

UCLASS()
class DUNGEONZERO_API ADZOriginActorBase : public AActor, public IDZCommonPlayRoleInterface
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

public:
	ADZOriginActorBase();

protected:
	virtual void BeginPlay() override;

#pragma endregion
//======================================================================================================================		
#pragma region 플레이롤
	
	//━━━━━━━━━━━━━━━━━━━━
	// 플레이롤
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	// IDZCommonPlayRoleInterface ~ 
	FORCEINLINE virtual EDZPlayRole GetPlayRole_Implementation() override { return PlayRole;}
	// ~ IDZCommonInteractInterface, IDZCommonPlayRoleInterface
	
protected:
	// 롤 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | OriginActor")
	EDZPlayRole PlayRole = EDZPlayRole::None;
#pragma endregion
//======================================================================================================================	
};
