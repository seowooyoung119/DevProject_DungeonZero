// All CopyRight by BooZaGameStudio // 


#include "FOR_INGAME/SECTION_AI/Library/DZStateTreeLibrary.h"
#include "Components/StateTreeAIComponent.h"

UStateTreeAIComponent* UDZStateTreeLibrary::GetStateTreeAIComponentFromActor(AActor* InActor)
{
	if (!IsValid(InActor))
	{
		return nullptr;
	}
	
	APawn* Pawn = Cast<APawn>(InActor);
	if (!IsValid(Pawn))
	{
		return nullptr;
	}
	
	AController* Controller = Cast<AController>(Pawn->GetController());
	if (!IsValid(Controller))
	{
		return nullptr;
	}
	
	UStateTreeAIComponent* StateTreeAIComponent = Controller->FindComponentByClass<UStateTreeAIComponent>();
	if (!IsValid(StateTreeAIComponent))
	{
		return nullptr;
	}
	
	return StateTreeAIComponent;
}

UStateTreeAIComponent* UDZStateTreeLibrary::GetStateTreeComponentFromController(AController* InController)
{
	UStateTreeAIComponent* StateTreeAIComponent = InController->FindComponentByClass<UStateTreeAIComponent>();
	if (!IsValid(StateTreeAIComponent))
	{
		return nullptr;
	}
	
	return StateTreeAIComponent;
}
