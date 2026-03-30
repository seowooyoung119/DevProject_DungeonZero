// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace DZ
{
	namespace Stage
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_STAGE_PREPARE);				// 준비 전 초기화
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_STAGE_READYNEWSTAGE)			// 준비 실시
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_STAGE_OPENDOOR)				// 문 열기 
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_STAGE_STAGECLAER)				// 스테이지 클리어
	}

	namespace Time
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_TIME_REDUCE);					// 타이머 감소 중
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_TIME_TIMEOVER);				// 타임 오버 됨.
	}
	
	namespace FindAnomaly
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_SEND_FIND_ANOMLAY);			// 어노말리인 것 같으면 이거다 찍을 때 호출하는 채널	
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_RESOULT_OF_FIND_ANOMLAY);		// 어노말리 찾기 결과 			
	}
}
