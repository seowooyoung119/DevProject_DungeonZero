// All CopyRight by BooZaGameStudio // 

#include "FOR_LIBRARY/LineTarce/DZTraceHelperLibrary.h"

//======================================================================================================================    
#pragma region 라인_트레이스

bool UDZTraceHelperLibrary::LineTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::LineTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::LineTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::LineTraceMulti(WorldContextObject, Start, End, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::LineTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::LineTraceMulti(WorldContextObject, Start, End, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

#pragma endregion
//======================================================================================================================    
#pragma region 박스_트레이스

bool UDZTraceHelperLibrary::BoxTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::BoxTraceSingle(WorldContextObject, Start, End, HalfSize, Orientation, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::BoxTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::BoxTraceSingle(WorldContextObject, Start, End, HalfSize, Orientation, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::BoxTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::BoxTraceMulti(WorldContextObject, Start, End, HalfSize, Orientation, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::BoxTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::BoxTraceMulti(WorldContextObject, Start, End, HalfSize, Orientation, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

#pragma endregion
//======================================================================================================================    
#pragma region 스피어_트레이스

bool UDZTraceHelperLibrary::SphereTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::SphereTraceSingle(WorldContextObject, Start, End, Radius, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::SphereTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::SphereTraceSingle(WorldContextObject, Start, End, Radius, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::SphereTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::SphereTraceMulti(WorldContextObject, Start, End, Radius, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::SphereTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::SphereTraceMulti(WorldContextObject, Start, End, Radius, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

#pragma endregion
//======================================================================================================================    
#pragma region 캡슐_트레이스

bool UDZTraceHelperLibrary::CapsuleTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::CapsuleTraceSingle(WorldContextObject, Start, End, Radius, HalfHeight, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::CapsuleTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::CapsuleTraceSingle(WorldContextObject, Start, End, Radius, HalfHeight, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHit, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::CapsuleTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    return UKismetSystemLibrary::CapsuleTraceMulti(WorldContextObject, Start, End, Radius, HalfHeight, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

bool UDZTraceHelperLibrary::CapsuleTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf, EDrawDebugTrace::Type DrawDebugType, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
{
    FVector End = Start + (Direction.GetSafeNormal() * Length);
    return UKismetSystemLibrary::CapsuleTraceMulti(WorldContextObject, Start, End, Radius, HalfHeight, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawTime);
}

#pragma endregion
//======================================================================================================================