// All CopyRight by BooZaGameStudio // 


#include "DungeonZero/Public/FOR_INGAME/SECTION_INTERACT/Comp/DZInteractComponent.h"

#include "DungeonZero/Public/FOR_LIBRARY/Getter/DZGetControllerLibrary.h"

//======================================================================================================================	
#pragma region 라이프_사이클
	
	//━━━━━━━━━━━━━━━━━━━━
	// 라이프 사이클
	//━━━━━━━━━━━━━━━━━━━━	

UDZInteractComponent::UDZInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDZInteractComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UDZInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TickInteract_internal();
}

void UDZInteractComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
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
	if (OwnerPlayerController.IsValid() && IsValid(OwnerPlayerController.Get())) return true;
	
	// 플레이어 컨트롤러 가져오기 	
	APlayerController* PC = UDZGetControllerLibrary::GetPlayerControllerFromComponent(GetOwner());
	if (!IsValid(PC)) return false;
	
	// 캐싱
	OwnerPlayerController = PC;
	
	// 후 검증 
	if (!OwnerPlayerController.IsValid() || !IsValid(OwnerPlayerController.Get())) return false;
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
	DrawInteractionDebugLine_internal(TraceStart, TraceEnd, HitResult, bHit);
	
	// 맞은 게 있으면 반환 
	if (HitResult.bBlockingHit) return HitResult.GetActor();
	
	// 없으면 nullptr 반환 
	return nullptr;
}

void UDZInteractComponent::DrawInteractionDebugLine_internal(const FVector& Start, const FVector& End, const FHitResult& HitResult, bool bHit)
{
	// 1. 색상 결정 (맞으면 녹색, 아니면 적색)
	FColor DebugColor = bHit ? FColor::Green : FColor::Red;

	// 2. 라인 그리기 (무조건 실행)
	DrawDebugLine(GetWorld(),Start,End,DebugColor,false, 0.1f, 0, 1.0f);

	// 3. 충돌 시에만 해당 위치에 스피어 그리기
	if (bHit) DrawDebugSphere(GetWorld(),HitResult.ImpactPoint, 10.0f,12, DebugColor,false, 0.1f);
}

void UDZInteractComponent::DoInteractUILogicAfterLineTrace()
{
	
}

#pragma endregion 
//======================================================================================================================