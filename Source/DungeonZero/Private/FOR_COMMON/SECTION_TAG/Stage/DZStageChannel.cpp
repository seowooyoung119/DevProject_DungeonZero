// All CopyRight by BooZaGameStudio // 


#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"

namespace DZ
{
	namespace OriginMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_ORIGIN_VISIBILE_NOTICE,"DZ.MSG.Origin.VisibleNotice");				
	}
	
	namespace TimeMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_REDUCE, "DZ.MSG.Time.Reduce");				
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_TIMEOVER, "DZ.MSG.Time.TimeOver");		
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_MIN_NOITCE, "DZ.MSG>Time.MinNotice");			
	}
	
	namespace FindAnomalyMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_SEND_FIND_ANOMLAY, "DZ.MSG.FindAnomaly.Send");			
		UE_DEFINE_GAMEPLAY_TAG(DZ_RESOULT_OF_FIND_ANOMLAY, "DZ.MSG.FindAnomaly.Result");		
	}
	
	namespace GameModeMSG
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_GAMEMODE_DEADCOUNT, "DZ.MSG.GameMode.DeadCount");	
		UE_DEFINE_GAMEPLAY_TAG(DZ_GAMEMODE_DEADRESET, "DZ.MSG.GameMode.DeadReset");	
	}
}
