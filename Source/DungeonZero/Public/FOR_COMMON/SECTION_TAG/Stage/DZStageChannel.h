// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace DZ
{
	namespace PlayerMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_PLAYER_CANMOVEANDSEE);		// 플레이어 움직임 및 시야 토글		
	}
	
	namespace OriginMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_ORIGIN_VISIBILE_NOTICE);		// 원본 액터 숨김 처리 토글
	}
	
	namespace StageMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_STAGE_CURRENTLEVEL_NOTICE);	// 현재 레벨 알림	
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_STAGE_REMAINANOMLAY_NOTICE)	// 남은 어노말리 알림
	}
	
	namespace EndingMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_STAGE_ENDING_NOTICE);	// 마지막 스테이지 클리어	
	}
	
	namespace DoorMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_DOOR_DOORRESET);				// 문 리셋
		
	}
	
	namespace TimeMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_TIME_TIMERESET);				// 타이머 리셋
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_TIME_REDUCE);					// 타이머 감소 중
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_TIME_TIMEOVER);				// 타임 오버 됨.
	}
	
	namespace FindAnomalyMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_SEND_FIND_ANOMLAY);			// 어노말리인 것 같으면 이거다 찍을 때 호출하는 채널	
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_RESOULT_OF_FIND_ANOMLAY);		// 어노말리 찾기 결과 			
	}
	
	namespace AIMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_SEND_AIGC) // AI GC 
	}
	
	namespace GameModeMSG
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_GAMEMODE_DEADCOUNT);	// 플레이어가 죽을 때마다 호출
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(DZ_GAMEMODE_DEADRESET);	// 스테이지 초기화 시 호출 
	}
	
}
