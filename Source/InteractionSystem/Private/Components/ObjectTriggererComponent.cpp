// Amasson


#include "Components/ObjectTriggererComponent.h"
#include "Interfaces/Triggerable.h"
#include "GameFramework/GameStateBase.h"

UObjectTriggererComponent::UObjectTriggererComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UObjectTriggererComponent::BeginPlay()
{
	Super::BeginPlay();

	GlobalObjectTriggerer = GetGlobalObjectTriggererComponent();
}


void UObjectTriggererComponent::ExecuteTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	if (IsValid(TriggerableObject) && TriggerableObject->Implements<UTriggerable>())
	{
		ETriggerMode TriggerMode = ITriggerable::Execute_GetTriggerMode(TriggerableObject);
		switch (TriggerMode)
		{
		case ETriggerMode::TM_Server:
			Server_ExecuteTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
			break;
		case ETriggerMode::TM_Client:
			Client_ExecuteTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
			break;
		case ETriggerMode::TM_Multicast:
			Server_MulticastExecuteTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
			break;
		}
	}
}

void UObjectTriggererComponent::ExecuteReleaseTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	if (IsValid(TriggerableObject) && TriggerableObject->Implements<UTriggerable>())
	{
		ETriggerMode TriggerMode = ITriggerable::Execute_GetTriggerMode(TriggerableObject);
		switch (TriggerMode)
		{
		case ETriggerMode::TM_Server:
			Server_ExecuteReleaseTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
			break;
		case ETriggerMode::TM_Client:
			Client_ExecuteReleaseTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
			break;
		case ETriggerMode::TM_Multicast:
			Server_MulticastExecuteReleaseTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
			break;
		}
	}
}


void UObjectTriggererComponent::Server_ExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_Trigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

void UObjectTriggererComponent::Client_ExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_Trigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

void UObjectTriggererComponent::Server_MulticastExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	UObjectTriggererComponent* ObjectTriggerer = GlobalObjectTriggerer;
	if (!IsValid(ObjectTriggerer))
		ObjectTriggerer = this;
	ObjectTriggerer->NetMulticast_ExecuteTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

void UObjectTriggererComponent::NetMulticast_ExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_Trigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

void UObjectTriggererComponent::Server_ExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_ReleaseTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

void UObjectTriggererComponent::Client_ExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_ReleaseTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

void UObjectTriggererComponent::Server_MulticastExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	UObjectTriggererComponent* ObjectTriggerer = GlobalObjectTriggerer;
	if (!IsValid(ObjectTriggerer))
		ObjectTriggerer = this;
	ObjectTriggerer->NetMulticast_ExecuteReleaseTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

void UObjectTriggererComponent::NetMulticast_ExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_ReleaseTrigger(TriggerableObject, TriggererController, Triggerer, Tag, Payload);
}

UObjectTriggererComponent* UObjectTriggererComponent::GetGlobalObjectTriggererComponent() const
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	UObjectTriggererComponent *GlobalTrigger = GameState->GetComponentByClass<UObjectTriggererComponent>();

	if (!IsValid(GlobalTrigger))
		UE_LOG(LogTemp, Warning, TEXT("No UObjectTriggererComponent in GameState... Multicast triggers won't be executed by everyone"));

	return GlobalTrigger;
}
