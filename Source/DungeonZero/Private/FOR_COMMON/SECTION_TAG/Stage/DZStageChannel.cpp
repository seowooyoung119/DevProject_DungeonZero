// All CopyRight by BooZaGameStudio // 


#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"

namespace DZ
{
	namespace PlayerMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_PLAYER_CANMOVEANDSEE,"DZ.MSG.Player.CanMoveAndSee");				
	}
	
	namespace OriginMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_ORIGIN_VISIBILE_NOTICE,"DZ.MSG.Origin.VisibleNotice");				
	}
	
	namespace StageMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_STAGE_CURRENTLEVEL_NOTICE, "DZ.MSG.Stage.CurrentLevelNotice");
		UE_DEFINE_GAMEPLAY_TAG(DZ_STAGE_REMAINANOMLAY_NOTICE,"DZ.MSG.Stage.RemainAnomalyNotice");
	}
	
	namespace EndingMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_STAGE_ENDING_NOTICE, "DZ.MSG.Stage.EndingNotice");		
	}
	
	namespace DoorMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_DOOR_DOORRESET, "DZ.MSG.Door.Reset");
		
	}
	
	namespace TimeMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_TIMERESET, "DZ.MSG.Time.Reset");
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_REDUCE, "DZ.MSG.Time.Reduce");				
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_TIMEOVER, "DZ.MSG.Time.TimeOver");				
	}
	
	namespace FindAnomalyMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_SEND_FIND_ANOMLAY, "DZ.MSG.FindAnomaly.Send");			
		UE_DEFINE_GAMEPLAY_TAG(DZ_RESOULT_OF_FIND_ANOMLAY, "DZ.MSG.FindAnomaly.Result");		
	}
}
