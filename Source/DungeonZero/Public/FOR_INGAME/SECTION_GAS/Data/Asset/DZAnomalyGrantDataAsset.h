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
	// 오버랩시 활성화
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	bool bActivateOnTrigger = true;
	// 오버랩 종료시 비활성화
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	bool bDeactivateOnTrigger = true;
	
};
UCLASS()
class DUNGEONZERO_API UDZAnomalyGrantDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DZ")
	TArray<FDZAnomalyGrantData> GrantedAbilities; 
};
