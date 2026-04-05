// All CopyRight From YulRyongGameStudio //

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ITEM_AND_INVENTORY/Inventory/Inventory/Comp/A_Master/DZInventoryMasterComponent.h"
#include "DZHotKeyInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONZERO_API UDZHotKeyInventoryComponent : public UDZInventoryMasterComponent
{
	GENERATED_BODY()
	
//======================================================================================================================	
#pragma region REP_API
	
	//━━━━━━━━━━━━━━━━━━━━
	// REP API
	//━━━━━━━━━━━━━━━━━━━━
	
private:
	UFUNCTION() 
	void OnRep_ActiveHotKeyIndex();
	
#pragma endregion
//======================================================================================================================	
#pragma region 라이프_사이클
	
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
public:
	UDZHotKeyInventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
#pragma endregion	
//======================================================================================================================	
#pragma region 핫키
	
	//━━━━━━━━━━━━━━━━━━━━
	// 핫키 
	//━━━━━━━━━━━━━━━━━━━━	

public:
	// 활성화 중인 핫키 슬롯 인덱스를 반환
	FORCEINLINE int32 GetActiveHotKeyIndex() { return ActiveHotKeyIndex; }
	FORCEINLINE void SetActiveHotKeyIndex(int32 InActiveHotKeyIndex) { ActiveHotKeyIndex = InActiveHotKeyIndex; }

protected:	
	UPROPERTY(ReplicatedUsing = OnRep_ActiveHotKeyIndex, VisibleAnywhere, BlueprintReadOnly, Category = "DZ | Hotkey")
	int32 ActiveHotKeyIndex = -1;
	
#pragma endregion 
//======================================================================================================================	

};
