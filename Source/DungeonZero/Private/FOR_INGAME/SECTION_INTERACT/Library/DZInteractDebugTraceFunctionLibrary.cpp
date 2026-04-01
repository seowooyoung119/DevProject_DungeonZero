// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_INTERACT/Library/DZInteractDebugTraceFunctionLibrary.h"

void UDZInteractDebugTraceFunctionLibrary::DrawInteractionDebugLine_Lib(const UWorld* InWorld, const FVector& Start, const FVector& End, const FHitResult& HitResult, bool bHit)
{
	if (!IsValid(InWorld)) return;
	
	// 1. 색상 결정 (맞으면 녹색, 아니면 적색)
	FColor DebugColor = bHit ? FColor::Green : FColor::Red;

	// 2. 라인 그리기 (무조건 실행)
	DrawDebugLine(InWorld,Start,End,DebugColor,false, 0.1f, 0, 1.0f);

	// 3. 충돌 시에만 해당 위치에 스피어 그리기
	if (bHit) DrawDebugSphere(InWorld,HitResult.ImpactPoint, 10.0f,12, DebugColor,false, 0.1f);
}
