// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DZAnomalyGrantDataAsset.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FDZAnomalyGrantData
{
	GENERATED_BODY()
	// 부여할 어빌리티 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	TSubclassOf<UGameplayAbility> GameplayAbility;
	// 트리거로 동작하는 어빌리티면 체크
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	bool bActivateOnTrigger = false;
	
};
UCLASS()
class DUNGEONZERO_API UDZAnomalyGrantDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	TArray<FDZAnomalyGrantData> GrantedAbilities; 
};
