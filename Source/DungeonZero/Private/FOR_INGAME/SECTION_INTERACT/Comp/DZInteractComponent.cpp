// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_INTERACT/Comp/DZInteractComponent.h"
#include "DungeonZero/Public/FOR_LIBRARY/Getter/DZGetControllerLibrary.h"
#include "FOR_INGAME/SECTION_INTERACT/Interface/DZCommonInteractInterface.h"
#include "FOR_INGAME/SECTION_INTERACT/Library/DZInteractDebugLibrary.h"
#include "FOR_INGAME/SECTION_INTERACT/Library/DZInteractDebugTraceFunctionLibrary.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZInteractComponent::UDZInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDZInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickInteract_internal();
}

void UDZInteractComponent::TickInteract_internal()
{
	// 캐싱 확인 (Valid 체크 있음)
	if (!HasCachingOwnerPlayerController_internal()) return;
	
	// 갱신 
	LastInteractActor = CurrentInteractActor;
	
	// 라인 트레이스 실시 
	CurrentInteractActor = LineTrace_internal();

	// 추 처리
	DoInteractUILogicAfterLineTrace();
}

bool UDZInteractComponent::HasCachingOwnerPlayerController_internal()
{
	// 이미 오너 캐싱햇으면 리턴 
	if (IsValid(OwnerPlayerController)) return true;
	
	// 플레이어 컨트롤러 가져오기 	
	APlayerController* PC = UDZGetControllerLibrary::GetPlayerControllerFromComponent(GetOwner());
	if (!IsValid(PC)) return false;
	
	// 캐싱
	OwnerPlayerController = PC;
	
	// 후 검증 
	if (!IsValid(OwnerPlayerController)) return false;
	return true;
}

AActor* UDZInteractComponent::LineTrace_internal()
{
	FVector EyeLocation;
	FRotator EyeRotation;
	
	// 1. 카메라의 위치와 회전값 가져오기 (화면 중앙 기준점)
	OwnerPlayerController->GetPlayerViewPoint(EyeLocation, EyeRotation);

	// 2. 시작점과 끝점 계산
	FVector TraceStart = EyeLocation;
	FVector TraceEnd = TraceStart + (EyeRotation.Vector() * InteractDistance);

	// 3. 트레이스 설정 (자기 자신은 무시)
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	// 4. 라인 트레이스 실행 (ECC_Visibility 채널 사용)
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,TraceStart,TraceEnd,ECC_Visibility,QueryParams);
	
	// [추가] 디버그 함수 호출 (결과값과 HitResult를 같이 전달)
	if (bDebugDrawLine) UDZInteractDebugTraceFunctionLibrary::DrawInteractionDebugLine_Lib(GetWorld(), TraceStart, TraceEnd, HitResult, bHit);
	if (bDebugDrawLine) UDZInteractDebugLibrary::DebugInteractActors(GetOwner(), CurrentInteractActor, LastInteractActor);
	
	// 맞은 게 있으면 반환 
	if (HitResult.bBlockingHit) return HitResult.GetActor();
	
	// 없으면 nullptr 반환 
	return nullptr;
}

void UDZInteractComponent::DoInteractUILogicAfterLineTrace()
{
	if (!IsValid(OwnerPlayerController)) return;
	if (OwnerPlayerController->IsLocalPlayerController() == false) return;
	
	// 1. 상태 변화 체크: 현재 액터와 마지막 액터가 같다면 로직 수행 불필요
	if (CurrentInteractActor == LastInteractActor) return;
	
	// 2. [지난 액터 처리] 마지막 액터가 유효했다면 위젯 끄기
	if (IsValid(LastInteractActor.Get()) && LastInteractActor->GetClass()->ImplementsInterface(UDZCommonInteractInterface::StaticClass()))
	{
		IDZCommonInteractInterface::Execute_ToggleInteractWidget(LastInteractActor.Get(), false);
	}
	
	// 3. [현재 액터 처리] 현재 액터가 유효하다면 위젯 켜기
	if (IsValid(CurrentInteractActor.Get()) && CurrentInteractActor->GetClass()->ImplementsInterface(UDZCommonInteractInterface::StaticClass()))
	{
		IDZCommonInteractInterface::Execute_ToggleInteractWidget(CurrentInteractActor.Get(), true);
	}
}

#pragma endregion 
//======================================================================================================================