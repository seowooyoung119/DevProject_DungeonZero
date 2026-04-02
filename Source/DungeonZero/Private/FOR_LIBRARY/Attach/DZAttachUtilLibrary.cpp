// All CopyRight by BooZaGameStudio // 


#include "FOR_LIBRARY/Attach/DZAttachUtilLibrary.h"
#include "GameFramework/Character.h"

UStaticMeshComponent* UDZAttachUtilLibrary::GetStaticMeshComponentByMeshTag(AActor* InActor, const FName& InMeshTag)
{
	// 타겟 체크
	if (!IsValid(InActor)) return nullptr;
    
	// 스태틱 메쉬 다 가져옴
	TArray<UStaticMeshComponent*> MeshComps;
	InActor->GetComponents<UStaticMeshComponent>(MeshComps);
    
	// 태그 체크
	for (UStaticMeshComponent* Mesh : MeshComps)
	{
		if (Mesh && Mesh->ComponentHasTag(InMeshTag))
		{
			
			if (IsValid(GEngine))
			{
				FString DebugMsg = FString::Printf(TEXT("DZ_LOG: [%s] 찾음 (Actor: %s)"), *Mesh->GetName(), *InActor->GetName());
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, DebugMsg);
			}
			
			return Mesh;
		}
	}
    
	// [깜빡 방지] 태그를 찾지 못했을 경우 경고를 띄우고 루트를 시도합니다.
	ensureMsgf(false, TEXT("DZ_LOG: [%s] 액터에서 [%s] 태그를 가진 StaticMesh를 찾지 못했습니다!"), *InActor->GetName(), *InMeshTag.ToString());
    
	// 루트를 캐스팅 후 반환 
	return Cast<UStaticMeshComponent>(InActor->GetRootComponent());
}

USkeletalMeshComponent* UDZAttachUtilLibrary::GetSkeletalMeshComponentByMeshTag(AActor* InActor, const FName& InMeshTag)
{
	// 타겟 체크
	if (!IsValid(InActor)) return nullptr;

	// 스태틱 메쉬 다 가져옴
	TArray<USkeletalMeshComponent*> SkinnedComps;
	InActor->GetComponents<USkeletalMeshComponent>(SkinnedComps);

	// 태그 체크
	for (USkeletalMeshComponent* Mesh : SkinnedComps)
	{
		if (Mesh && Mesh->ComponentHasTag(InMeshTag))
		{
			return Mesh;
		}
	}

	// [깜빡 방지] 스켈레탈 메시 태그 검색 실패 시 경고
	ensureMsgf(false, TEXT("DZ_LOG: [%s] 액터에서 [%s] 태그를 가진 SkinnedMesh를 찾지 못했습니다!"), *InActor->GetName(), *InMeshTag.ToString());
 
	// 루트를 캐스팅 후 반환 
	return Cast<USkeletalMeshComponent>(InActor->GetRootComponent());
}

USkeletalMeshComponent* UDZAttachUtilLibrary::GetCharacterMeshComponent(AActor* InActor)
{
	// 타겟 체크
	if (!IsValid(InActor)) return nullptr;
	
	// 캐스팅
	ACharacter* target = Cast<ACharacter>(InActor);
	if (!IsValid(target)) return nullptr;
	
	return target->GetMesh();
}
