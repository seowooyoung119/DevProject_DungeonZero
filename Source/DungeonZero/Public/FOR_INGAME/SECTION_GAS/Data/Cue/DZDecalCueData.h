// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZDecalCueData.generated.h"

USTRUCT(BlueprintType)
struct FDZDecalCueData
{
	GENERATED_BODY()

	// 부착할 데칼 액터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | DecalCue")
	TSubclassOf<AActor> DecalClass;
	// 부착 위치 소켓 명
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | DecalCue")
	FName SocketName = FName("DecalAttach");
};
