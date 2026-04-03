// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZDecalCueData.generated.h"

USTRUCT(BlueprintType)
struct FDZDecalCueData
{
	GENERATED_BODY()

	// 부착할 데칼 액터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Decal")
	TSubclassOf<AActor> DecalClass;
	// 부착 위치 소켓 명
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Decal")
	FName SocketName = FName("DecalAttach");
	// 타겟 메시 컴포넌트 태그
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Decal")
	FName TargetMeshTag = "MainMesh";
};

// 데칼 데이터 배열 구조체
USTRUCT(BlueprintType)
struct FDZDecalCueDataArray
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ | Cue | Decal")
	TArray<FDZDecalCueData> DecalCueDataArray;
};
