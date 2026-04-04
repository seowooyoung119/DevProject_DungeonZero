// // All CopyRight by BooZaGameStudio // 
//
//
// #include "FOR_INGAME/SECTION_GAS/GE_Player/A_READ_ME_GUIDE_THIS_IS_TEXT/DZGE_GameplayEffectGuideDocument.h"
// #include "FOR_INGAME/SECTION_GAS/AttributeSet/DZAttributeSet.h"
// PRAGMA_DISABLE_DEPRECATION_WARNINGS
//
// /*
// =============================================================================
//  📌 C++에서 GE를 설정하는 핵심 패턴
//  ─────────────────────────────────────────────────────────────────────────────
//  생성자 안에서 GE를 설정할 때 자주 쓰는 헬퍼 패턴:
//  [Modifier 추가 공통 패턴]
//  ①  FGameplayModifierInfo 구조체 생성
//  ②  Attribute, ModifierOp, ModifierMagnitude 설정
//  ③  Modifiers 배열에 Add
//  [SetByCaller 패턴]
//  ④  Ability 쪽에서 ApplyGameplayEffectSpecToTarget() 전에
//      Spec.SetSetByCallerMagnitude(Tag, Value) 호출
//  [태그 설정 공통 패턴]
//  ⑤  FGameplayTagContainer에 태그를 추가
//  ⑥  InheritableOwnedTagsContainer.Added.AddTag() 등으로 GE에 설정
// =============================================================================
//  */
//
// UDZGE_GameplayEffectGuideDocument::UDZGE_GameplayEffectGuideDocument()
// {
// }
//  
// /*
//  =============================================================================
//
//   ┌──────────────────────────────────────────────────────────────────────────┐
//   │  예시 1. 즉시 대미지 GE (Instant + SetByCaller)                            │
//   └──────────────────────────────────────────────────────────────────────────┘
//
//   사용 시나리오:
//    - 어빌리티(Ability)가 피격을 감지했을 때 이 GE를 적용합니다.
//    - 실제 대미지 수치는 Ability에서 계산해서 SetByCaller로 GE에 전달합니다.
//    - GE는 그 값을 받아서 Health 어트리뷰트를 즉시 깎습니다.
//
//   Ability에서 이 GE를 사용하는 코드 예시:
//
//     // 1단계: GE 스펙 생성
//     FGameplayEffectSpecHandle DamageSpecHandle =  SourceASC->MakeOutgoingSpec(UDZGE_Damage::StaticClass(), AbilityLevel, EffectContext);
//
//     // 2단계: 실제 수치를 Tag로 주입 (SetByCaller)
//     DamageSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), -50.0f); 
//
//     // 3단계: 대상에게 적용
//     SourceASC->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), TargetASC);
//
// =============================================================================
//
// */
// UDZGE_Document_Damage::UDZGE_Document_Damage()
// {
// }	
//
// void UDZGE_Document_Damage::PostInitProperties()
// {
// 	Super::PostInitProperties();
//
//     // ── 1. 지속 정책: Instant (즉시 적용 후 사라짐) ──────────────────────────
//     DurationPolicy = EGameplayEffectDurationType::Instant;
//  
//     // ── 2. Modifier 설정 ─────────────────────────────────────────────────────
//     {
//         FGameplayModifierInfo ModInfo;
//  
//         // 어떤 어트리뷰트를 수정할지
//         ModInfo.Attribute = UDZAttributeSet::GetHealthAttribute();
//  
//         // 연산 방식: Additive (더하기) 음수 값을 SetByCaller로 주입하면 사실상 빼기가 됩니다.
//         ModInfo.ModifierOp = EGameplayModOp::Additive;
//  
//         // 수치 결정 방식: SetByCaller
//         // → Ability에서 런타임에 값을 직접 넣어줍니다.
//         // → Tag는 Ability와 이 GE 양쪽에서 동일하게 사용해야 합니다.
//         FSetByCallerFloat SetByCallerData;
//         SetByCallerData.DataTag = FGameplayTag::RequestGameplayTag(FName("Document.Data.Damage"));
//         ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(SetByCallerData);
//  
//         Modifiers.Add(ModInfo);
//     }
//  
//     // ── 3. 이 GE의 태그 (이 GE 자신의 정체성 태그) ───────────────────────────
//     // 다른 GE가 "GameplayEffect.Damage" 태그를 가진 GE를 제거하거나 면역 처리할 수 있습니다.
// 	InheritableOwnedTagsContainer.Added.AddTag(FGameplayTag::RequestGameplayTag("Document.GameplayEffect.Damage"));
// 	
//     // ── 4. GameplayCue 설정 (피격 이펙트/사운드 트리거) ──────────────────────
//     // "GameplayCue.Hit.Physical" 태그에 연결된 GameplayCueNotify가 실행됩니다.
//     FGameplayEffectCue HitCue;
//     HitCue.GameplayCueTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayCue.Hit.Physical")));
//     GameplayCues.Add(HitCue);
// }
//
//
//
// /*
// =============================================================================
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  예시 2. 즉시 회복 GE (Instant + ScalableFloat 고정 수치)                   │
//  └──────────────────────────────────────────────────────────────────────────┘
//  
//  사용 시나리오:
//   - 회복 포션 사용 시 즉시 HP를 50 회복시킵니다.
//   - 수치가 고정이므로 SetByCaller 없이 ScalableFloat으로 바로 설정합니다.
//   
//  Ability에서 사용하는 코드:
//    FGameplayEffectSpecHandle HealSpec = SourceASC->MakeOutgoingSpec(UDZGE_HealInstant::StaticClass(), 1.0f, EffectContext);
//    SourceASC->ApplyGameplayEffectSpecToTarget(*HealSpec.Data.Get(), TargetASC);
//
//    // → 별도의 SetByCaller 없이 바로 적용
//    
// =============================================================================
// */
//     
// UDZGE_Document_HealInstant::UDZGE_Document_HealInstant()
// {
// }	
//
// void UDZGE_Document_HealInstant::PostInitProperties()
// {
// 	Super::PostInitProperties();
// 	
//     // ── 1. 지속 정책 ──────────────────────────────────────────────────────────
//     DurationPolicy = EGameplayEffectDurationType::Instant;
//  
//     // ── 2. Modifier: Health +50 (고정 수치) ────────────────────────────────
//     {
//         FGameplayModifierInfo ModInfo;
//         ModInfo.Attribute = UDZAttributeSet::GetHealthAttribute();
//         ModInfo.ModifierOp = EGameplayModOp::Additive;
//  
//         // ScalableFloat: 코드에서 바로 고정 수치를 지정합니다.
//         // 레벨별로 다른 수치를 주려면 UCurveTable을 연결할 수 있습니다.
//         ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(50.0f));
//  
//         Modifiers.Add(ModInfo);
//     }
//  
//     // ── 3. GE 태그 ────────────────────────────────────────────────────────────
// 	InheritableOwnedTagsContainer.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayEffect.Heal")));
//     
// 	
//     // ── 4. GameplayCue 설정 (피격 이펙트/사운드 트리거) ──────────────────────
//     // "GameplayCue.Hit.Physical" 태그에 연결된 GameplayCueNotify가 실행됩니다.
//     FGameplayEffectCue HealCue;
//     HealCue.GameplayCueTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayCue.Heal.Physical")));
//     GameplayCues.Add(HealCue);
// }
//  
// /*
// =============================================================================
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  예시 3. 지속 회복 GE (HasDuration + Period = 도트 힐)                      │
//  └──────────────────────────────────────────────────────────────────────────┘
//
//  사용 시나리오:
//   - 재생 포션을 마시면 10초 동안 매 초마다 HP를 5씩 회복합니다.
//   - DurationPolicy = HasDuration + Period = 1초로 설정합니다.
//
//  동작 방식:
//   - GE 적용 시작 → 10초 타이머 시작
//   - 1초마다 Modifier 재실행 (HP +5)
//   - 10초 후 GE 자동 종료
//
// =============================================================================
// */
//
// UDZGE_Document_HealOverTime::UDZGE_Document_HealOverTime()
// {
// }	
//
// void UDZGE_Document_HealOverTime::PostInitProperties()
// {
// 	Super::PostInitProperties();
// 	
//     // ── 1. 지속 정책: HasDuration (일정 시간 후 자동 종료) ───────────────────
//     DurationPolicy = EGameplayEffectDurationType::HasDuration;
//  
//     // ── 2. 지속 시간: 10초 ───────────────────────────────────────────────────
//     DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(10.0f));
//  
//     // ── 3. 반복 주기: 1초마다 Modifier 실행 ─────────────────────────────────
//     Period = FScalableFloat(1.0f);
//  
//     // ── 4. 적용 즉시 첫 번째 틱 실행 여부 ───────────────────────────────────
//     // true  → 적용 즉시 한 번 + 이후 1초마다 (총 11회 = 즉시1 + 10초×1)
//     // false → 1초 후부터 시작 (총 10회)
//     bExecutePeriodicEffectOnApplication = false;
//  
//     // ── 5. Modifier: Health +5 ───────────────────────────────────────────────
//     {
//         FGameplayModifierInfo ModInfo;
//         ModInfo.Attribute = UDZAttributeSet::GetHealthAttribute();
//         ModInfo.ModifierOp = EGameplayModOp::Additive;
//         ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));
//         Modifiers.Add(ModInfo);
//     }
//  
//     // ── 6. Target에게 부여할 태그 ────────────────────────────────────────────
//     // GE가 활성화된 10초 동안 Target에 "State.Regenerating" 태그가 붙습니다.
//     // 다른 시스템이 이 태그를 감지해서 재생 중 UI를 표시하는 등 활용 가능합니다.
//     InheritableOwnedTagsContainer.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.State.Regenerating")));
//  
//     // ── 7. GameplayCue (재생 이펙트) ─────────────────────────────────────────
//     // GE가 지속되는 동안 재생 파티클/사운드를 루프 재생합니다.
//     FGameplayEffectCue RegenCue;
//     RegenCue.GameplayCueTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayCue.Buff.Regen")));
//     GameplayCues.Add(RegenCue);
// }
//  
// /*
// =============================================================================
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  예시 4. 독 대미지 GE (Infinite + Period = 도트 대미지)                     │
//  └──────────────────────────────────────────────────────────────────────────┘
//
//  사용 시나리오:
//   - 적에게 독 공격을 하면 해독하지 않는 한 매 초 10씩 HP가 줄어듭니다.
//   - 해독 아이템이나 해독 스킬이 RemoveGameplayEffectByTag()로 이 GE를 제거합니다.
//
//  독 제거 코드 (해독 아이템/스킬에서):
//    FGameplayTagContainer PoisonTagContainer;
//    PoisonTagContainer.AddTag(FGameplayTag::RequestGameplayTag(FName("GameplayEffect.Poison")));
//    TargetASC->RemoveActiveEffectsWithGrantedTags(PoisonTagContainer);
//
// =============================================================================
// */
//
// UDZGE_Document_PoisonDamage::UDZGE_Document_PoisonDamage()
// {
// }
//
// void UDZGE_Document_PoisonDamage::PostInitProperties()
// {
//     Super::PostInitProperties();
//
// 	// ── 1. 지속 정책: Infinite (수동으로 제거할 때까지 영원히 지속) ──────────
//     DurationPolicy = EGameplayEffectDurationType::Infinite;
//  
//     // ── 2. 반복 주기: 1초마다 Modifier 실행 ─────────────────────────────────
//     Period = FScalableFloat(1.0f);
//     bExecutePeriodicEffectOnApplication = true;  // 독에 걸리자마자 즉시 첫 번째 틱
//  
//     // ── 3. Modifier: Health -10 (독 대미지) ─────────────────────────────────
//     {
//         FGameplayModifierInfo ModInfo;
//         ModInfo.Attribute = UDZAttributeSet::GetHealthAttribute();
//         ModInfo.ModifierOp = EGameplayModOp::Additive;
//         // 음수 값 = 감소
//         ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(-10.0f));
//         Modifiers.Add(ModInfo);
//     }
//  
//     // ── 4. 이 GE의 식별 태그 (해독 시 이 태그로 찾아서 제거합니다) ──────────
//     InheritableGameplayEffectTags.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayEffect.Poison")));
//  
//     // ── 5. Target에게 "독" 상태 태그 부여 ────────────────────────────────────
//     InheritableOwnedTagsContainer.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.State.Debuff.Poison")));
//  
//     // ── 6. 스택 설정: 같은 독이 중첩되면 최대 3스택까지 강화 ─────────────────
//     // AggregateBySource = 공격자마다 독립적인 스택 (A가 건 독과 B가 건 독이 따로 쌓임)
//     // AggregateByTarget = Target 기준으로 하나의 스택 풀 (덮어씌우는 개념)
//     StackingType = EGameplayEffectStackingType::AggregateByTarget;
//     StackLimitCount = 3;  // 최대 3중독까지 가능
//  
//     // 스택될 때마다 지속시간 리셋 여부
//     StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;
//     
//     // 스택될 때마다 주기 타이머 리셋 여부
//     StackPeriodResetPolicy = EGameplayEffectStackingPeriodPolicy::ResetOnSuccessfulApplication;
//     
//     // ── 7. GameplayCue (재생 이펙트) ─────────────────────────────────────────
//     // GE가 지속되는 동안 재생 파티클/사운드를 루프 재생합니다.
//     FGameplayEffectCue RegenCue;
//     RegenCue.GameplayCueTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayCue.DeBuff.Poison")));
//     GameplayCues.Add(RegenCue);
//     
// }
//  
// /*
// =============================================================================
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  예시 5. 속도 버프 GE (HasDuration + 조건부 태그 + MMC 예시)                 │
//  └──────────────────────────────────────────────────────────────────────────┘
//
//  사용 시나리오:
//   - "질풍" 스킬 사용 시 8초 동안 이동속도를 1.3배 증가시킵니다.
//   - 단, "State.Stunned" 태그(기절)가 붙어 있으면 버프 효과가 일시 중단됩니다.
//   - 기절이 풀리면 버프가 다시 활성화됩니다. (GE는 제거되지 않음)
//
// =============================================================================
// */
//
// UDZGE_Document_SpeedBuff::UDZGE_Document_SpeedBuff()
// {
// }
// void UDZGE_Document_SpeedBuff::PostInitProperties()
// {
//     Super::PostInitProperties();
// 	
//     // ── 1. 지속 정책: 8초 유지 ───────────────────────────────────────────────
//     DurationPolicy = EGameplayEffectDurationType::HasDuration;
//     DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(8.0f));
//  
//     // ── 2. Modifier: MoveSpeed를 1.3배 (Multiplicative) ─────────────────────
//     // Multiplicative 연산: CurrentValue *= (1 + Magnitude)
//     // Magnitude = 0.3 → Speed * 1.3 (30% 증가)
//     {
//         FGameplayModifierInfo ModInfo;
//         ModInfo.Attribute = UDZAttributeSet::GetStaminaAttribute();
//         ModInfo.ModifierOp = EGameplayModOp::Multiplicitive;
//         ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(1.3f));
//         Modifiers.Add(ModInfo);
//     }
//  
//     // ── 3. OngoingTagRequirements: 기절 상태면 이 버프 효과를 비활성화 ────────
//     // RequirePresence : 이 태그가 있어야 효과 활성화 (없으면 비활성화)
//     // RequireAbsence  : 이 태그가 없어야 효과 활성화 (있으면 비활성화)
//     OngoingTagRequirements.IgnoreTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.State.Stunned")));
//     
//     // → 기절(State.Stunned) 태그가 붙어있으면 속도 버프 효과가 일시 중단됩니다.
//     // → 기절이 풀리면 자동으로 버프가 다시 활성화됩니다.
//  
//     // ── 4. ApplicationTagRequirements: 이미 슈퍼 아머 상태면 적용 안 함 ──────
//     // 어빌리티가 GE를 적용하려 할 때 이 조건을 먼저 체크합니다.
//     // 조건 불만족이면 GE 자체가 적용되지 않습니다.
//     ApplicationTagRequirements.IgnoreTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.State.SuperArmor")));
//  
//     // ── 5. Target에게 속도 버프 태그 부여 ────────────────────────────────────
//     InheritableOwnedTagsContainer.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.State.Buff.SpeedUp")));
//     
//     // ── 7. GameplayCue (재생 이펙트) ─────────────────────────────────────────
//     // GE가 지속되는 동안 재생 파티클/사운드를 루프 재생합니다.
//     FGameplayEffectCue RegenCue;
//     RegenCue.GameplayCueTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayCue.Buff.SpeedUp")));
//     GameplayCues.Add(RegenCue);
// }
//  
// /* 
// =============================================================================
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  예시 6. 달리기 스태미나 소모 GE (Infinite + Period)                        │
//  └──────────────────────────────────────────────────────────────────────────┘
//
//  사용 시나리오:
//   - 달리기 Ability가 활성화되면 이 GE를 적용합니다.
//   - 달리기를 멈추면 Ability가 EndAbility()에서 이 GE를 제거합니다.
//   - 스태미나가 0이 되면 AttributeSet의 PostGameplayEffectExecute에서
//     달리기 Ability를 강제 종료시킵니다.
//
//  달리기 Ability에서 적용/제거 예시:
//    // 적용 (달리기 시작 시)
//    SprintEffectHandle = ApplyGameplayEffectToOwner(this, UDZGE_SprintStaminaDrain::StaticClass(), 1.0f);
//
//    // 제거 (달리기 종료 시)
//    BP_RemoveGameplayEffectFromOwnerWithHandle(SprintEffectHandle);
//
// =============================================================================
// */
//
// UDZGE_Document_SprintStaminaDrain::UDZGE_Document_SprintStaminaDrain()
// {
// }
//
// void UDZGE_Document_SprintStaminaDrain::PostInitProperties()
// {
//     Super::PostInitProperties();
// 	
//     // ── 1. 지속 정책: Infinite (달리기 Ability가 직접 제거) ──────────────────
//     DurationPolicy = EGameplayEffectDurationType::Infinite;
//  
//     // ── 2. 반복 주기: 0.1초마다 스태미나 소모 (부드러운 게이지 감소 효과) ────
//     Period = FScalableFloat(0.1f);
//     bExecutePeriodicEffectOnApplication = false;  // 달리기 시작 직후 0.1초 후부터 소모
//  
//     // ── 3. Modifier: Stamina -2 (0.1초마다, 즉 초당 -20 소모) ───────────────
//     {
//         FGameplayModifierInfo ModInfo;
//         ModInfo.Attribute = UDZAttributeSet::GetStaminaAttribute();
//         ModInfo.ModifierOp = EGameplayModOp::Additive;
//         ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(-2.0f));
//         Modifiers.Add(ModInfo);
//     }
//  
//     // ── 4. 이 GE가 활성화되려면 달리기 가능 태그가 있어야 함 ─────────────────
//     // 스턴, 넉백 등 상태이상으로 달리기가 불가능할 때 이 소모도 멈춥니다.
//     OngoingTagRequirements.RequireTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.State.CanSprint")));
// }
//  
// /* 
// =============================================================================
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  예시 7. ExecutionCalculation을 활용한 복합 대미지 GE                       │
//  └──────────────────────────────────────────────────────────────────────────┘
//  
//  사용 시나리오:
//   - RPG 스타일의 복잡한 대미지 공식을 사용합니다.
//   - 공식: 실제대미지 = (Source.AttackPower * 1.5 - Target.Defense) * CritMultiplier
//   - 이런 복잡한 계산은 Modifier로 처리 불가 → ExecutionCalculation을 사용합니다.
//   
//  ExecutionCalculation 클래스 (UDZExecCalc_Damage)를 별도로 만들어야 합니다.
//  [ExecutionCalculation 가이드]를 참고하세요.
//  
// =============================================================================
// */
//
// UDZGE_Document_DamageWithExecution::UDZGE_Document_DamageWithExecution()
// {
// }
//
// void UDZGE_Document_DamageWithExecution::PostInitProperties()
// {
//     Super::PostInitProperties();
// 	
//     // ── 1. 지속 정책: Instant ─────────────────────────────────────────────────
//     DurationPolicy = EGameplayEffectDurationType::Instant;
//  
//     // ── 2. ExecutionCalculation 등록 ─────────────────────────────────────────
//     // Modifier 배열 대신 Executions 배열에 계산 클래스를 등록합니다.
//     // 실제 어트리뷰트 수정은 ExecutionCalculation 클래스 내부에서 처리합니다.
//     FGameplayEffectExecutionDefinition ExecDef;
//     // ExecDef.CalculationClass = UDZExecCalc_Damage::StaticClass();  // 실제 사용 시 주석 해제
//     Executions.Add(ExecDef);
//  
//     // ── 3. 태그 및 Cue는 동일하게 설정 ─────────────────────────────────────
//     InheritableGameplayEffectTags.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.GameplayEffect.Damage")));
// 	
// }
//  
// /* 
// // =============================================================================
// //
// //  ┌──────────────────────────────────────────────────────────────────────────┐
// //  │  예시 8. 스택형 공격력 버프 GE (Stacking)                                   │
// //  └──────────────────────────────────────────────────────────────────────────┘
// //
// //  사용 시나리오:
// //   - 적을 공격할 때마다 공격력이 5씩 쌓입니다. 최대 5스택 (공격력 +25).
// //   - 각 스택은 10초 지속. 적용 시마다 10초 타이머가 리셋됩니다.
// //   - 5스택이 된 후 다시 쌓으려 하면 무시됩니다.
// //
// // =============================================================================
// */
// UDZGE_Document_StackingAttackBuff::UDZGE_Document_StackingAttackBuff()
// {
// }
//
// void UDZGE_Document_StackingAttackBuff::PostInitProperties()
// {
//     Super::PostInitProperties();
// 	
//     // ── 1. 지속 정책: 10초 유지 ──────────────────────────────────────────────
//     DurationPolicy = EGameplayEffectDurationType::HasDuration;
//     DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(10.0f));
//  
//     // ── 2. Modifier: AttackPower +5 ──────────────────────────────────────────
//     {
//         FGameplayModifierInfo ModInfo;
//         ModInfo.Attribute = UDZAttributeSet::GetAttackPowerAttribute();
//         ModInfo.ModifierOp = EGameplayModOp::Additive;
//         ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));
//         Modifiers.Add(ModInfo);
//     }
//  
//     // ── 3. 스택 설정 ──────────────────────────────────────────────────────────
//     // AggregateByTarget: 누가 공격하든 Target 기준으로 하나의 스택 풀 관리
// 	StackingType = EGameplayEffectStackingType::AggregateByTarget;
//
// 	StackLimitCount = 5;  // 최대 5스택
//  
//     // 스택 추가될 때마다 10초 타이머 리셋 (마지막 적용 시점 기준)
//     StackDurationRefreshPolicy = EGameplayEffectStackingDurationPolicy::RefreshOnSuccessfulApplication;
//  
//     // 5스택 초과 시도 시 GE 적용 거부 여부
//     // true  = 5스택에서 추가 적용 시 실패 (콜백으로 알림)
//     // false = 5스택에서 추가 시도 시 조용히 무시
//     bDenyOverflowApplication = false;
//  
//     // ── 4. 태그 ───────────────────────────────────────────────────────────────
//     InheritableOwnedTagsContainer.Added.AddTag(FGameplayTag::RequestGameplayTag(FName("Document.State.Buff.AttackUp")));
// }
// PRAGMA_DISABLE_DEPRECATION_WARNINGS