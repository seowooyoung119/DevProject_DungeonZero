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
		// 어노말리
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_EYELIGHT);
		
		// 어노말리 종료
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_END_SHADOW);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_END_FOOTPRINTGHOST);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_END_CEILINGEYES);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_ANOMALY_END_CHANGE);
		
		
		// 플레이어
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_CUE_PLAYER_DEAD);
		
	}
}
