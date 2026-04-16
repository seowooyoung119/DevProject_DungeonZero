// All CopyRight by BooZaGameStudio // 

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DZStageBalanceDataTable.generated.h"

USTRUCT(BlueprintType)
struct FDZStageBalanceRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="룸")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="시간")
	float Time = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="최소 어노말리 갯수")
	int32 MinAnomalyCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DZ", DisplayName="최대 어노말리 갯수")
	int32 MaxAnomalyCount = 5;
};

/*
< 레벨 밸런스를 어떻게 할 것인가 > 

레벨에 관여해야할 것 같은 요소.

1. 층의 레벨 ( == 층수)
2. 제한 시간 
3. 최소 어노말리 갯수
4. 최대 어노말리 갯수
5. 각 룸마다 배치 가능한 어노말리 타입, 갯수, 최대 티어  

[Step 1] 이번 스테이지의 총 어노말리 개수 결정
>> 조건 : 만약 최대 어노말리 원본 갯수보다 많으면 최대 어노말리 원본 갯수로 제한
==>> 결과 : 이번 스테이지에 배치될 총 어노말리 갯수

[Step 2] 각 방별 '배치 후보군' 필터링
각 방을 돌면서, 해당 방에 들어갈 수 있는 어노말리 원본(Master Data) 리스트를 미리 뽑아둡니다.
>> 조건: AllowedTypes에 포함되는가? AND MaxTier 이하인가?
>> 조건 : 후보군 리스트의 크기가 MaxCapacity보다 작다면, 실제 최대치는 후보군 리스트의 크기가 됩니다.
==>> 결과 : 방마다 실제로 배치 가능한 후보 원본 배열들

[Step 3] 가용 자원 분배 (가장 중요!)
>> 1. 배치 가능한 방 리스트업: (현재 배치된 개수 < MaxCapacity) 이고 (후보군에 아직 남은 어노말리가 있는) 방들만 추립니다.
>> 2. 방 랜덤 선택: 리스트업된 방 중 하나를 무작위로 고릅니다.
>> 3. 개수 추가: 해당 방에 배치할 어노말리 개수를 +1 합니다.
>> 4. 반복: 총합이 TargetTotal이 될 때까지 반복합니다.
>> 5. 만약 모든 방이 꽉 찼는데 TargetTotal에 도달하지 못했다면? 실제 가능한 최대치에서 멈춥니다.
>. 6. 총 어노말리 갯수를 실제 배치 가능한 최대치로 클램프.
==>> 결과 : 방마다 배치 가능한 갯수

[Step 4] 가용 자원 분배 실시
>> 1. 방마다 배치 가능한 "갯수"만큼 "실제로 배치 가능한 후보 원본 배열들" 무작위로 뽑음.
>> 2. 스테이지의 최대 티어에 따른 티어별 어노말리로 바꿈.
>> 3. 모든 방을 전부 그렇게 실시.
==>> 결과 : "배치 가능한 어노말리 타입"으로 필터링된 방마다 "배치 가능한 갯수" 만큼 "최대 티어"에 따른 어노말리 생성됨.
*/

/*
< 게임 플레이 재미 및 발전 요소 >

1. 게임이 처음엔 찾기 쉬움. -> 티어가 낮은 이상현상들 존재
2. 게임이 점점 어려워짐 -> 티어 높은 이상현상들 존재.
3. 양피지의 패널티 -> 흑마법의 부작용 같은 요소 발생 (ex 못 걷는다. 못 듣는다. 못 말한다. 이따금 귀신이 보인다. 이따금 귀신 소리가 들린다. 횟불이 꺼진다 등등)
4. 특수 이벤트의 패널티 -> ex 어느 방에 이상현상이 있다. 알려줌. 다음 스테이지 때 전체 패널티가 생김. 예를 들면 불을 켤 수 없다 등등.
*/


