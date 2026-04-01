// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FOR_COMMON/SECTION_GAMEPLAYMESSAGE/Invnetory/DZInventoryUpdateMSG.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Data/Struct/InventoryCompData/DZInventoryCompData.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "DZInventoryUI.generated.h"

class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class DUNGEONZERO_API UDZInventoryUI : public UUserWidget
{
	GENERATED_BODY()
	
//======================================================================================================================
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프_사이클
	//━━━━━━━━━━━━━━━━━━━━
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

#pragma endregion
//=====================================================================================================================	
#pragma region 게임플레이메시지
	
	//━━━━━━━━━━━━━━━━━━━━
	// 게임플레이메시지
	//━━━━━━━━━━━━━━━━━━━━
	
protected:
	
	// 인벤토리 업데이트 요청 메시지를 받았을 때 실행될 함수
	void OnInventoryUpdateMessageReceived_internal(FGameplayTag Channel, const FDZInventoryUpdateMessage& Message);
	
	// 핸들 
	FGameplayMessageListenerHandle ListenerHandle;
	
#pragma endregion
//=====================================================================================================================
#pragma region 위젯업데이트API
	
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯업데이트API
	//━━━━━━━━━━━━━━━━━━━━	
	
protected:
	// 초기화 함수
	void InitializeFixedSlots_internal();
	
public:
	// 인벤토리 데이터를 받아 UI를 새로고침하는 함수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RefreshInventory(FDZInventoryCompData& InventoryCompData);
	
#pragma endregion
//======================================================================================================================
#pragma region 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━
	// 위젯_모듈
	//━━━━━━━━━━━━━━━━━━━━

protected:
	
	// 인벤토리 그리드 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> InventoryGrid = nullptr;

#pragma endregion
//======================================================================================================================
#pragma region Data		

	//━━━━━━━━━━━━━━━━━━━━
	// Data
	//━━━━━━━━━━━━━━━━━━━━
protected:
	
	// 생성된 슬롯들을 보관하는 캐시 배열 
	UPROPERTY()
	TArray<UUserWidget*> CachedSlotWidgets;

	// 고정할 슬롯의 총 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 FixedSlotCount = 5;

	// 생성할 슬롯 위젯의 클래스 (Blueprint에서 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> SlotWidgetClass = nullptr;
	
	// 한 줄에 표시할 슬롯 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 ColumnsCount = 10;

	// 타겟 인벤토리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	EDZInventoryCompType TargetInventoryComp = EDZInventoryCompType::None;
	
#pragma endregion
//======================================================================================================================	
};
