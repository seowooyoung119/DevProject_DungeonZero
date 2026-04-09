// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "FOR_INGAME/SECTION_ANOMALY/Character/Base/DZAnomalyCharacterBase.h"
#include "ADZAnomalyFootPrintGhost.generated.h"

UCLASS()
class DUNGEONZERO_API AADZAnomalyFootPrintGhost : public ADZAnomalyCharacterBase
{
	GENERATED_BODY()

//======================================================================================================================	
#pragma region 라이프_사이클

	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	
	
public:
	AADZAnomalyFootPrintGhost();
	

#pragma endregion
//======================================================================================================================	
#pragma region 어노말리_엔딩_펑션
	
	//━━━━━━━━━━━━━━━━━━━━
	// 어노말리 엔딩 펑션
	//━━━━━━━━━━━━━━━━━━━━	
public:
	// GAS로 하기 비효율적이거나 액터와 연관이 되어 있을 경우 이 인터페이스의 API를 상속하여 로직을 추가한 뒤 GAS의 EndAbility 에서 인터페이스 호출 
	virtual void AnomalySealAdditionalFunction_Implementation() override;
	
#pragma endregion
//======================================================================================================================		
};
