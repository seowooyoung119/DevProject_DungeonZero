// All CopyRight by BooZaGameStudio // 


#include "FOR_COMMON/SECTION_TAG/Stage/DZStageChannel.h"

namespace DZ
{
	namespace Stage
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_STAGE_PREPARE, "DZ.Stage.Prepare");
		UE_DEFINE_GAMEPLAY_TAG(DZ_STAGE_READYNEWSTAGE, "DZ.Stage.ReadyNewStage");
		UE_DEFINE_GAMEPLAY_TAG(DZ_STAGE_OPENDOOR, "DZ.Stage.OpenDoor");
		
		
		UE_DEFINE_GAMEPLAY_TAG(DZ_STAGE_STAGECLAER, "DZ.Stage.StageClear");			
	}
	
	namespace Time
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_REDUCE, "DZ.Time.Reduce");				
		UE_DEFINE_GAMEPLAY_TAG(DZ_TIME_TIMEOVER, "DZ.Time.TimeOver");				
	}
	
	namespace FindAnomaly
	{
		UE_DEFINE_GAMEPLAY_TAG(DZ_SEND_FIND_ANOMLAY, "DZ.FindAnomaly.Send");			
		UE_DEFINE_GAMEPLAY_TAG(DZ_RESOULT_OF_FIND_ANOMLAY, "DZ.FindAnomaly.Result");		
	}
}
