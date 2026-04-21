// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "DZFakeAnomalySeeInfo.generated.h"

/**
 * 가짜 이상현상 목록 시야 정보
 * 어떤 플레이어가 볼 수 있는지에 대한 정보를 이상현상에게 넘겨주기 위함
 */
USTRUCT(BlueprintType)
struct DUNGEONZERO_API FDZFakeAnomalySeeInfo
{
	GENERATED_BODY()
	
	// 볼 수 있는 플레이어 목록
	UPROPERTY()
	TArray<TObjectPtr<APlayerState>> CanSeePlayers;
	
	// 원본 포인터 
	UPROPERTY()
	TObjectPtr<AActor> OriginActor;
};
