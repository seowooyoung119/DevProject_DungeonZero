// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZAttachUtilLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZAttachUtilLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// 스태틱 메쉬 컴포넌트 가져다줌. (태그로 찾음)
	static UStaticMeshComponent* GetStaticMeshComponentByMeshTag(AActor* InActor, const FName& InMeshTag);

	// 스켈레탈 메쉬 가져다줌 (태그로 찾음)
	static USkeletalMeshComponent* GetSkeletalMeshComponentByMeshTag(AActor* InActor, const FName& InMeshTag);
	
	// 스켈레탈 메쉬 가져다줌 (플레이어)
	static USkeletalMeshComponent* GetCharacterMeshComponent(AActor* InActor);
	
	
};
