// // All CopyRight by BooZaGameStudio // 
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "GameplayEffectExecutionCalculation.h"
// #include "GameplayModMagnitudeCalculation.h"
// #include "FOR_INGAME/SECTION_GAS/AttributeSet/DZAttributeSet.h"
// #include "DZExecCalc_GuideDocument.generated.h"
//
// /**
//  * 
//  */
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZExecCalc_GuideDocument : public UGameplayEffectExecutionCalculation
// {
// 	GENERATED_BODY()
// };
//
// /*
//  📌 ExecutionCalculation 작성법
//
//  ExecutionCalculation(이하 ExecCalc)은 GAS에서 가장 강력한 계산 도구입니다.
//  Source와 Target 양쪽의 어트리뷰트를 자유롭게 읽어서 복잡한 공식을 계산하고
//  결과를 어트리뷰트에 직접 적용할 수 있습니다.
//  
// */
//
// //  ── DZExecCalc_Damage.h ────────────────────────────────────────────────────
//  UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
//  class UDZGE_ExecCalcDocument_Damage : public UGameplayEffectExecutionCalculation
//  {
//      GENERATED_BODY()
//  public:
//      UDZGE_ExecCalcDocument_Damage();
//      
//      // 이 함수가 GE 적용 시 호출되는 핵심 계산 함수입니다.
//      virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
//  };
//
// //  ── DZExecCalc_Damage.cpp ──────────────────────────────────────────────────
//  
// // 어트리뷰트 캡처 선언 (읽어올 어트리뷰트를 미리 등록)
//   struct FDZDamageStatics
//   {
//       // Source 어트리뷰트 (공격자)
//       DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
//       // Target 어트리뷰트 (피격자)
//       DECLARE_ATTRIBUTE_CAPTUREDEF(Health)
//
//       FDZDamageStatics()
//       {
//           // 어트리뷰트, 누구로부터 캡처, 스냅샷 여부
//           // Source = 공격자, Target = 피격자
//           // Snapshot = true → GE 적용 '시점'의 값 고정 (이후 변경 무시)
//           // Snapshot = false → 실제 실행 시점의 최신 값 사용 (보통 권장)
//           DEFINE_ATTRIBUTE_CAPTUREDEF(UDZAttributeSet, AttackPower, Source, false)
//           DEFINE_ATTRIBUTE_CAPTUREDEF(UDZAttributeSet, Health,      Target, false)
//       }
//   };
//
//   static const FDZDamageStatics& DamageStatics()
//   {
//       static FDZDamageStatics Statics;
//       return Statics;
//   }
//
// inline UDZGE_ExecCalcDocument_Damage::UDZGE_ExecCalcDocument_Damage()
//   {
//       // 생성자에서 캡처할 어트리뷰트를 GAS에 등록합니다.
//       RelevantAttributesToCapture.Add(DamageStatics().AttackPowerDef);
//       RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
//   }
//
// inline void UDZGE_ExecCalcDocument_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
//   {
//       // ── 어트리뷰트 값 읽어오기 ──────────────────────────────────────────
//       FAggregatorEvaluateParameters EvalParams;
//       EvalParams.SourceTags = ExecutionParams.GetOwningSpec().CapturedSourceTags.GetAggregatedTags();
//       EvalParams.TargetTags = ExecutionParams.GetOwningSpec().CapturedTargetTags.GetAggregatedTags();
//
//       float AttackPower = 0.0f;
//       ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AttackPowerDef, EvalParams, AttackPower);
//
//       // ── SetByCaller로 외부에서 주입된 기본 대미지 읽기 ─────────────────
//       float BaseDamage = 0.0f;
//       ExecutionParams.AttemptCalculateCapturedAttributeMagnitudeWithBase(DamageStatics().AttackPowerDef, EvalParams, 0.0f, BaseDamage);
//
//       // ── 대미지 공식 ─────────────────────────────────────────────────────
//       float FinalDamage = FMath::Max(0.0f, (AttackPower * 1.5f));
//
//       // 치명타 체크
//       bool bIsCritical = FMath::FRand() < 0.2f;  // 20% 치명타 확률
//       if (bIsCritical) FinalDamage *= 2.0f;
//
//       // ── 계산 결과를 어트리뷰트에 적용 ──────────────────────────────────
//       // OutExecutionOutput에 "이 어트리뷰트를 이만큼 바꿔라"를 등록합니다.
//       // 실제 어트리뷰트 수정은 GAS 내부 시스템이 처리합니다.
//       OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().HealthProperty,EGameplayModOp::Additive, -FinalDamage));
//   }
//
// /*
//  📌 MMC (ModMagnitudeCalculation) 작성법
//  MMC는 Modifier의 수치 하나를 커스텀 공식으로 계산할 때 사용합니다.
//  ExecCalc보다 가볍고 단순한 계산에 적합합니다.
//  사용 예: 최대 HP의 10%를 회복하는 힐 (고정 50이 아닌 비율 기반)
// */
//
// //  ── DZMMC_HealByPercentage.h ───────────────────────────────────────────────
//
//   UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
//   class UDZMMC_Document_HealByPercentage : public UGameplayModMagnitudeCalculation
//   {
//       GENERATED_BODY()
//   public:
//       UDZMMC_Document_HealByPercentage();
//
//       // 이 함수가 Modifier의 수치를 결정합니다. float 하나를 반환합니다.
//       virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
//
//   private:
//       // 읽어올 어트리뷰트 캡처 정의
//       FGameplayEffectAttributeCaptureDefinition MaxHealthDef;
//   };
//
// // ── UDZMMC_Document_HealByPercentage.cpp ─────────────────────────────────────────────
//
// inline UDZMMC_Document_HealByPercentage::UDZMMC_Document_HealByPercentage()
//   {
//       // MaxHealth를 Target에서 읽어옵니다.
//       MaxHealthDef.AttributeToCapture = UDZAttributeSet::GetMaxHealthAttribute();
//       MaxHealthDef.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
//       MaxHealthDef.bSnapshot          = false;
//       RelevantAttributesToCapture.Add(MaxHealthDef);
//   }
//
// inline float UDZMMC_Document_HealByPercentage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
//   {
//       FAggregatorEvaluateParameters EvalParams;
//       EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
//       EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
//
//       float MaxHealth = 0.0f;
//       GetCapturedAttributeMagnitude(MaxHealthDef, Spec, EvalParams, MaxHealth);
//
//       // 최대 HP의 10%를 반환 → Modifier가 이 값을 Health에 더합니다.
//       return MaxHealth * 0.1f;
//   }
//
//   // ── GE에서 MMC 사용 ────────────────────────────────────────────────────────
//
//   // GE 생성자 안에서:
// /*
//   FGameplayModifierInfo ModInfo;
//   ModInfo.Attribute  = UDZAttributeSet::GetHealthAttribute();
//   ModInfo.ModifierOp = EGameplayModOp::Additive;
//
//   FCustomCalculationBasedFloat MMCData;
//   MMCData.CalculationClassMagnitude = UDZMMC_HealByPercentage::StaticClass();
//   ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(MMCData);
//   Modifiers.Add(ModInfo);
// */
