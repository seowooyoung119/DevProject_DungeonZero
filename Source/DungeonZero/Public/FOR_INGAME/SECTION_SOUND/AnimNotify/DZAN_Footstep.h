// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DZAN_Footstep.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAN_Footstep : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	// 발 소켓 명
	UPROPERTY(EditAnywhere, Category = "DZ | Footstep")
	FName SocketName = TEXT("foot_l");
	// 왼발인지 오른발인지 
	UPROPERTY(EditAnywhere, Category = "DZ | Footstep")
	bool bIsLeft = true;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
