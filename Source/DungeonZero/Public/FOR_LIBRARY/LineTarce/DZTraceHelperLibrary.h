// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DZTraceHelperLibrary.generated.h"

UCLASS()
class DUNGEONZERO_API UDZTraceHelperLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

//======================================================================================================================    
#pragma region 라인_트레이스

    // 싱글 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool LineTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 싱글 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool LineTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool LineTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool LineTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

#pragma endregion
//======================================================================================================================    
#pragma region 박스_트레이스

    // 싱글 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool BoxTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 싱글 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool BoxTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool BoxTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool BoxTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, const FVector HalfSize, const FRotator Orientation, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

#pragma endregion
//======================================================================================================================       
#pragma region 스피어_트레이스

    // 싱글 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool SphereTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 싱글 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool SphereTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool SphereTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool SphereTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

#pragma endregion
//======================================================================================================================    
#pragma region 캡슐_트레이스

    // 싱글 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool CapsuleTraceSingleToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 싱글 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool CapsuleTraceSingleDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, FHitResult& OutHit, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 포인트
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool CapsuleTraceMultiToPoint(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

    // 멀티 - 방향
    UFUNCTION(BlueprintCallable, Category = "DZ | HelperLibrary | Trace", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ActorsToIgnore", AdvancedDisplay = "TraceColor, TraceHitColor, DrawTime"))
    static bool CapsuleTraceMultiDirectional(const UObject* WorldContextObject, const FVector Start, const FVector Direction, float Length, float Radius, float HalfHeight, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, TArray<FHitResult>& OutHits, bool bIgnoreSelf = true, EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::ForDuration, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 1.0f);

#pragma endregion
//======================================================================================================================    

};