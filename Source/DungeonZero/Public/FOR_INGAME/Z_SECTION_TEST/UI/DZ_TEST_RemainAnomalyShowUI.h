// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DZ_TEST_RemainAnomalyShowUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZ_TEST_RemainAnomalyShowUI : public UUserWidget
{
	GENERATED_BODY()
	
//=====================================================================================================================
#pragma region 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	// 남은 이상현상 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainAnomalyTextBlock = nullptr;

#pragma endregion
//=====================================================================================================================
#pragma region 이상현상_테스트
	//━━━━━━━━━━━━━━━━━━━━
	// 이상현상_테스트
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	void UpdateRemainAnomaly(const int32 InRemainAnomaly);
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DZ")
	int32 RemainAnomaly = -1;
	
#pragma endregion
//=====================================================================================================================	
};
