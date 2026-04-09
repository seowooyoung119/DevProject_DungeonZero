// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

// 풀 푸쉬 충돌 방지를 위해 임시로 여기에 두는 태그.
// 반드시 DZGameplayCueTag 로 옮겨야 함.

namespace DZ
{
	namespace TempGameplayCue
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_EYELIGHT);
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_END_SHADOW);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_END_FOOTPRINTGHOST);
		
	}
}
