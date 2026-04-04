// // All CopyRight by BooZaGameStudio // 
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "GameplayEffect.h"
// #include "DZGE_GameplayEffectGuideDocument.generated.h"
//
//
// /**
// ───────────────────────────────────────────────────────────────────────────── 
//  📌 [ GAS 가이드 : UGameplayEffect 마스터 매뉴얼 ]
// ─────────────────────────────────────────────────────────────────────────────
//
//
// ─────────────────────────────────────────────────────────────────────────────
//  📌 GameplayEffect(GE)란 무엇인가?
// ─────────────────────────────────────────────────────────────────────────────
//  GameplayEffect는 GAS(Gameplay Ability System)에서 "어트리뷰트 및 태그를 바꾸는
//  모든 행위"를 담당하는 데이터 오브젝트입니다.
//
//  쉽게 말해:
//   - 대미지를 준다    → GameplayEffect로 HP를 깎는다
//   - 버프를 건다      → GameplayEffect로 공격력 수치를 올린다
//   - 상태이상을 건다  → GameplayEffect로 태그를 부여하고 이동속도를 낮춘다
//   - 회복 포션을 쓴다 → GameplayEffect로 HP를 올린다
//
//  GameplayEffect는 "직접 로직을 실행"하지 않습니다.
//  "어떤 값을 어떻게 바꿀지"에 대한 명세(데이터)를 정의하고,
//  GAS 내부 시스템이 그 명세를 읽어서 실제로 실행합니다.
//
//
//
// ─────────────────────────────────────────────────────────────────────────────
//  📌 GE가 적용되는 흐름 (큰 그림)
// ─────────────────────────────────────────────────────────────────────────────
//
//  [Ability / 코드] → ApplyGameplayEffectToTarget()
//                             ↓
//                  [GameplayEffect 인스턴스 생성]
//                             ↓
//                  [DurationPolicy 확인] → Instant / HasDuration / Infinite
//                             ↓
//                  [Modifiers 순서대로 어트리뷰트에 적용]
//                             ↓
//                  [ExecutionCalculations 실행 (있다면)]
//                             ↓
//                  [GameplayTags 부여 / 제거]
//                             ↓
//                  [Cues 트리거 → 사운드/VFX 재생]
//              
//              
//              
// ─────────────────────────────────────────────────────────────────────────────
//  📌 핵심 변수(프로퍼티) 완전 가이드
//  ─────────────────────────────────────────────────────────────────────────────
//  
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  1. DurationPolicy  (EGameplayEffectDurationType)                        │
//  └──────────────────────────────────────────────────────────────────────────┘
//  GE가 "얼마나 지속될지"를 결정합니다. GE의 성격 자체를 결정하는 가장 중요한 설정.
//  
//  ● Instant
//    - 적용되는 순간 딱 한 번 어트리뷰트를 변경하고 즉시 사라집니다.
//    - BaseValue를 직접 수정합니다. (영구적인 수치 변경)
//    - 사용처: 대미지, 회복 포션, 골드 획득, 경험치 획득
//    - ※ Infinite/HasDuration은 CurrentValue만 수정 → Instant만 BaseValue 수정
//    
//  ● HasDuration
//    - Duration (FScalableFloat)으로 지정한 초(秒)동안 유지되다가 자동 제거됩니다.
//    - 적용 중에는 CurrentValue를 수정하고, 종료되면 원래대로 돌아옵니다.
//    - 사용처: 5초간 이동속도 증가, 10초간 방어력 감소, 일정 시간 스턴
//    
//  ● Infinite
//    - 명시적으로 제거(RemoveGameplayEffect)하기 전까지 영원히 지속됩니다.
//    - 사용처: 패시브 버프 오라, 장비 착용 스탯 보너스, 달리기 중 스태미나 소모
//    
//  코드에서 설정하는 법:
//    DurationPolicy = EGameplayEffectDurationType::Instant;
//    DurationPolicy = EGameplayEffectDurationType::HasDuration;
//    DurationPolicy = EGameplayEffectDurationType::Infinite;
//    
//    
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  2. DurationMagnitude  (FGameplayEffectModifierMagnitude)                │
//  └──────────────────────────────────────────────────────────────────────────┘
//  GE가 지속되는 시간(초)을 설정합니다. (DurationPolicy가 HasDuration일 때만 유효합니다.)
//  설정 방법은 3가지:
//  
//    ① ScalableFloat : 레벨에 따라 달라지는 고정 수치 (커브 테이블 활용 가능)
//    ② AttributeBased : 특정 어트리뷰트 값으로 지속 시간 결정
//    ③ CustomCalculationClass : 직접 계산 클래스(MMC)로 결정
//    
//  코드에서 설정하는 법 (ScalableFloat 5초 예시):
//    DurationMagnitude = FGameplayEffectModifierMagnitude(FScalableFloat(5.0f));
//    
//    
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  3. Modifiers  (TArray<FGameplayModifierInfo>)                           │
//  └──────────────────────────────────────────────────────────────────────────┘
//  어트리뷰트를 실제로 "수정"하는 핵심 배열입니다.
//  하나의 GE 안에 여러 Modifier를 넣어서 여러 어트리뷰트를 한번에 바꿀 수 있습니다.
//  
//  FGameplayModifierInfo 구조:
//    ● Attribute (FGameplayAttribute)
//      - 수정할 대상 어트리뷰트
//      - ex) UDZAttributeSet::GetHealthAttribute()
//            UDZAttributeSet::GetMoveSpeedAttribute()
//            
//    ● ModifierOp (EGameplayModOp::Type)
//      ┌────────────────┬────────────────────────────────────────────────────┐
//      │ Additive       │ 더하기. ex) HP += 50                                │
//      │ Multiplicative │ 곱하기(배율 추가). ex) Speed *= (1 + 0.3)            │
//      │ Division       │ 나누기. ex) Damage /= 2                             │
//      │ Override       │ 덮어쓰기. ex) HP = 999 (무조건 이 값으로)             │
//      └────────────────┴────────────────────────────────────────────────────┘
//      
//    ● ModifierMagnitude (FGameplayEffectModifierMagnitude)
//      수치를 어떻게 결정할지의 방법론.
//      
//      ① ScalableFloat  : 고정 수치 (레벨별 커브 테이블 가능)
//         사용: FScalableFloat(50.0f)  → 50 고정
//         
//      ② AttributeBased : 다른 어트리뷰트 값을 기반으로 계산
//         사용: Source의 AttackPower 값으로 대미지 결정
//         
//      ③ CustomCalculationClass (MMC) : 별도의 UGameplayModMagnitudeCalculation
//         클래스를 만들어서 완전히 커스텀 계산
//         
//         사용: 복잡한 공식 (ex. 공격력 * 1.5 + 레벨 * 10 - 방어력)
//      ④ SetByCaller : 런타임에 외부에서 값을 주입
//         사용: Ability에서 계산한 실제 대미지를 GE에 전달할 때
//         
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  4. Period  (FScalableFloat)                                             │
//  └──────────────────────────────────────────────────────────────────────────┘
//  GE 효과가 "반복 실행"되는 주기(초)입니다.
//  Infinite 또는 HasDuration 정책과 함께 써서 "지속 효과"를 만듭니다.
//  Period = 0 이면 반복 없음 (기본값)
//  Period = 1 이면 1초마다 Modifier를 반복 적용
//  
//  사용처:
//   - 독 대미지 (매 초 HP -10)
//   - 초당 HP 회복 (매 초 HP +5)
//   - 달리기 중 스태미나 소모 (매 0.1초마다 스태미나 -1)
//  
//  코드에서 설정:
//    Period = FScalableFloat(1.0f);   // 1초마다 반복
//    bExecutePeriodicEffectOnApplication = true;  // 적용 즉시 첫 번째 틱 실행 여부
//    
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  5. Executions  (TArray<FGameplayEffectExecutionDefinition>)             │
//  └──────────────────────────────────────────────────────────────────────────┘
//  Modifier보다 훨씬 복잡한 계산이 필요할 때 사용합니다.
//  UGameplayEffectExecutionCalculation을 상속받은 클래스를 등록하면,
//  GE가 적용될 때 그 클래스의 Execute_Implementation()이 호출됩니다.
//  
//  Modifier와의 차이:
//   - Modifier : 단순한 사칙연산 (더하기, 곱하기 등)
//   - Execution: Source/Target 양쪽의 어트리뷰트를 자유롭게 읽어서
//                복잡한 공식으로 계산 가능 (RPG 대미지 공식 등)
//  
//  대표 사용처: 데미지 계산 (공격력, 치명타, 방어력, 방어 관통 등 모두 고려)
//  
//  코드에서 설정:
//    FGameplayEffectExecutionDefinition ExecDef;
//    ExecDef.CalculationClass = UDZExecCalc_Damage::StaticClass();
//    Executions.Add(ExecDef);
//
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  6. GameplayTags 관련 컨테이너들                                          │
//  └──────────────────────────────────────────────────────────────────────────┘
//  GE와 태그의 관계는 크게 5가지입니다.
//  
//  ● InheritableGameplayEffectTags (이 GE 자신의 태그)
//    - 이 GE 자체를 식별하는 태그입니다.
//    - 예: "GameplayEffect.Damage.Fire" → 화염 대미지 GE임을 나타냄
//    - 다른 GE가 이 태그를 가진 GE를 제거하거나 면역시킬 수 있음
//    
//  ● InheritableOwnedTagsContainer (적용 대상에게 부여할 태그)
//    - GE가 적용된 동안, Target의 ASC(AbilitySystemComponent)에 이 태그가 붙습니다.
//    - GE가 제거되면 태그도 같이 사라집니다.
//    - 예: "State.Burning" 태그를 Target에 부여 → 다른 시스템이 불타는 상태를 감지
//    
//  ● ApplicationTagRequirements (이 GE가 "적용되려면" 필요한 태그 조건)
//    - RequiredTags: Target이 이 태그를 가지고 있어야만 GE 적용
//    - IgnoreTags:   Target이 이 태그를 가지고 있으면 GE 적용 안 함
//    - 예: "State.Immune.Fire" 태그가 있으면 화염 GE를 무시
//    
//  ● OngoingTagRequirements (GE가 "활성 상태를 유지하려면" 필요한 태그 조건)
//    - HasDuration/Infinite GE에서 사용
//    - 조건을 만족 못하면 GE 효과가 일시 중단됨 (제거되지 않고 비활성화)
//    - 예: "State.Grounded" 태그가 없으면 속도 버프 효과 비활성화 (공중에 뜨면 무효)
//    
//  ● RemoveGameplayEffectsWithTags (적용 시 이 태그를 가진 다른 GE를 제거)
//    - 이 GE가 적용될 때, Target에서 특정 태그를 가진 다른 GE를 자동으로 제거
//    - 예: 해독 GE가 적용될 때 "GameplayEffect.Damage.Poison" 태그의 GE를 제거
//    
//  ● GrantedAbilities (GE 지속 중 어빌리티를 부여)
//    - GE가 활성화된 동안 Target에게 Ability를 추가로 부여
//    - GE가 제거되면 Ability도 같이 제거됨
//    - 예: 특정 버프 GE가 적용되는 동안 새로운 스킬을 사용 가능하게 함
//    
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  7. GameplayCues  (FGameplayEffectCue)                                   │
//  └──────────────────────────────────────────────────────────────────────────┘
//  GE 적용/제거/반복 시 비주얼/사운드 효과를 트리거합니다.
//  실제 로직과 시각효과를 분리해 주는 역할입니다.
//  
//  ● GameplayCueTags : 트리거할 Cue 태그 (예: "GameplayCue.Fire.Hit")
//  ● MinLevel / MaxLevel : 이 큐가 활성화되는 레벨 범위
//  
//  GameplayCue는 UGameplayCueNotify_Static (일회성) 또는 UGameplayCueNotify_Actor (지속형)를 상속받아 구현합니다.
//  
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  8. ChanceToApplyToTarget  (FScalableFloat, 0.0 ~ 1.0)                  │
//  └──────────────────────────────────────────────────────────────────────────┘
//  GE가 적용될 확률입니다.
//  1.0 = 100% 항상 적용 (기본값)
//  0.3 = 30% 확률로 적용 (디버프 상태이상 등에 활용)
//  
//  코드에서 설정: ChanceToApplyToTarget = FScalableFloat(0.3f);  // 30% 확률
//    
//  ┌──────────────────────────────────────────────────────────────────────────┐
//  │  9. StackingType / StackLimitCount / StackDurationRefreshPolicy          │
//  └──────────────────────────────────────────────────────────────────────────┘
//  같은 GE가 여러 번 적용될 때의 "중첩(스택)" 동작을 정의합니다.
//  
//  StackingType:
//   - None           : 중첩 없음. 같은 GE가 여러 번 독립적으로 존재
//   - AggregateBySource : Source(시전자)별로 스택. 각 Source가 독립적 스택 보유
//   - AggregateByTarget : Target별로 스택. Target 기준 하나의 스택으로 중첩
//  
//  StackLimitCount:
//   - 최대 중첩 횟수. 0이면 무제한.
//  
//  StackDurationRefreshPolicy:
//   - RefreshOnSuccessfulApplication : 스택될 때마다 지속시간 리셋
//   - NeverRefresh : 최초 적용 시 지속시간 고정, 스택돼도 리셋 안 함
//  
//  StackPeriodResetPolicy:
//   - ResetOnSuccessfulApplication : 스택될 때마다 주기 타이머 리셋
//   - NeverReset : 기존 주기 타이머 유지
//   
//   
//   
// =============================================================================
//  📌 재정의(Override) 가능한 주요 가상 함수
//  ─────────────────────────────────────────────────────────────────────────────
//  UGameplayEffect를 C++ 코드로 상속받을 때 override할 수 있는 함수들입니다.
//  
//  주의: GE 자체에서 override 가능한 함수는 많지 않습니다.
//        복잡한 커스텀 로직은 대부분 MMC나 ExecutionCalculation에서 처리합니다.
//        
//  ① void PostInitProperties() override
//     - 오브젝트 초기화 직후 호출됩니다.
//     - 생성자 대신 여기서 Modifier, Tag, Policy 등을 설정하면 안전합니다.
//     - 특히 어트리뷰트 참조가 필요한 초기화는 여기서 합니다.
//     
//  ② void PreReplicatedRemove(const FActiveGameplayEffectsContainer& InActiveGEContainer)
//     - 네트워크 복제 중 이 GE가 "제거"될 때 클라이언트에서 먼저 호출됩니다.
//     - UI 업데이트나 예측 처리에 활용 가능합니다.
//     
//  ③ void PostReplicatedAdd(const FActiveGameplayEffectsContainer& InActiveGEContainer)
//     - 네트워크 복제 중 이 GE가 "추가"될 때 클라이언트에서 호출됩니다.
//     
//  ④ void PostReplicatedChange(const FActiveGameplayEffectsContainer& InActiveGEContainer)
//     - 네트워크 복제 중 이 GE가 "변경"(스택 등)될 때 호출됩니다.
//     
//  ────────────────────────────────────────────────────────────────────────────
//  ※ 복잡한 커스텀 로직을 위한 별도 클래스들:
//  
//  [대미지/복잡한 계산]
//  UGameplayEffectExecutionCalculation 상속
//    → Execute_Implementation() 재정의
//    → Source/Target 양쪽 어트리뷰트 접근 가능
//    → 여러 어트리뷰트를 동시에 수정 가능
//    
//  [단일 어트리뷰트 커스텀 수치 계산]
//  UGameplayModMagnitudeCalculation 상속
//    → CalculateBaseMagnitude_Implementation() 재정의
//    → float 값 하나를 반환
//    → Modifier의 수치를 커스텀 공식으로 계산
//    
// =============================================================================
//
//
//
//
//
//
//
//
//
//
//  */
//
// //
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_GameplayEffectGuideDocument : public UGameplayEffect
// {
// 	GENERATED_BODY()
// 	
// public:
//     // =========================================================================
//     //  생성자: C++로 GE를 설정하는 핵심 공간
//     //
//     //  중요: GAS의 GE 프로퍼티들은 생성자에서 초기화합니다.
//     //  하위 클래스들이 이 생성자를 호출하고 자신의 세팅을 덮어씁니다.
//     //
//     //  실제 사용법은 DZGE_BaseGameplayEffect.cpp의 각 예시 클래스를 참고하세요.
//     // =========================================================================
//     UDZGE_GameplayEffectGuideDocument();
// };
//  
//  
// // =============================================================================
// //
// //  📌 실전 예시 클래스들 (선언부)
// //
// //  아래 클래스들의 실제 구현(생성자 내용)은 .cpp 파일을 참고하세요.
// //  각 클래스는 서로 다른 GE 패턴을 보여줍니다.
// //
// // =============================================================================
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 1. 즉시 대미지 GE (Instant + SetByCaller)
// //  사용처: 일반 공격, 스킬 피격
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_Damage : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_Damage();
// 	virtual void PostInitProperties() override;
// };
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 2. 즉시 회복 GE (Instant + ScalableFloat)
// //  사용처: 회복 포션, 힐 스킬
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_HealInstant : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_HealInstant();
// 	virtual void PostInitProperties() override;
// };
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 3. 지속 회복 GE (HasDuration + Period = 도트힐)
// //  사용처: 재생의 물약, 재생 버프 스킬
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_HealOverTime : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_HealOverTime();
// 	virtual void PostInitProperties() override;
// };
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 4. 독 대미지 GE (Infinite + Period = 도트 대미지)
// //  사용처: 독 상태이상, 번개 화상 등
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_PoisonDamage : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_PoisonDamage();
// 	virtual void PostInitProperties() override;
// };
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 5. 속도 버프 GE (HasDuration + 조건부 태그)
// //  사용처: 질풍 스킬, 속도 강화 포션
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_SpeedBuff : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_SpeedBuff();
// 	virtual void PostInitProperties() override;
// };
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 6. 달리기 스태미나 소모 GE (Infinite + Period)
// //  사용처: 달리기 중 스태미나 지속 소모
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_SprintStaminaDrain : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_SprintStaminaDrain();
// 	virtual void PostInitProperties() override;
// };
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 7. 복합 대미지 계산 GE (ExecutionCalculation 사용)
// //  사용처: RPG 스타일 복잡한 대미지 공식 (공격력, 방어력, 치명타 등 고려)
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_DamageWithExecution : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_DamageWithExecution();
// 	virtual void PostInitProperties() override;
// };
//  
//  
// // -----------------------------------------------------------------------------
// //  예시 8. 스택형 공격력 버프 GE (Stacking 활용)
// //  사용처: 공격할 때마다 쌓이는 버프 (최대 5스택)
// // -----------------------------------------------------------------------------
//
// //
// // ... 
// UCLASS(NotBlueprintable, NotBlueprintType, Abstract, Hidden)
// class DUNGEONZERO_API UDZGE_Document_StackingAttackBuff : public UGameplayEffect
// {
//     GENERATED_BODY()
// public:
//     UDZGE_Document_StackingAttackBuff();
// 	virtual void PostInitProperties() override;
// };