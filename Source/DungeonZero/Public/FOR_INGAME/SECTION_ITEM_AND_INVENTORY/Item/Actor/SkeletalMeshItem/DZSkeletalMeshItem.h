// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Item/Actor/Base/DZItemActorBase.h"
#include "DZSkeletalMeshItem.generated.h"

UCLASS(Blueprintable)
class DUNGEONZERO_API ADZSkeletalMeshItem : public ADZItemActorBase
{
	GENERATED_BODY()
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━
public:
	virtual void OnRep_bIsPickUpAble() override;

#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	ADZSkeletalMeshItem();
	virtual void BeginPlay() override;
	
#pragma endregion
//======================================================================================================================	
#pragma region 컴포넌트
	
	//━━━━━━━━━━━━━━━━━━━━
	// 컴포넌트 
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ | Item")
	TObjectPtr<USkeletalMeshComponent> ItemSkeletalMeshComp = nullptr;
		
#pragma endregion
//======================================================================================================================
#pragma region 피직스_콜리전
	
public:
	virtual void SetTogglePhysicsAndCollisions(bool InWantOn);
	
	
#pragma endregion
//======================================================================================================================	
	
};
