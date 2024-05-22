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


void UObjectTriggererComponent::ExecuteTrigger(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	if (IsValid(TriggerableObject) && TriggerableObject->Implements<UTriggerable>())
	{
		ETriggerMode TriggerMode = ITriggerable::Execute_GetTriggerMode(TriggerableObject);
		switch (TriggerMode)
		{
		case ETriggerMode::TM_Server:
			Server_ExecuteTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
			break;
		case ETriggerMode::TM_Client:
			Client_ExecuteTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
			break;
		case ETriggerMode::TM_Multicast:
			Server_MulticastExecuteTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
			break;
		}
	}
}

void UObjectTriggererComponent::ExecuteReleaseTrigger(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	if (IsValid(TriggerableObject) && TriggerableObject->Implements<UTriggerable>())
	{
		ETriggerMode TriggerMode = ITriggerable::Execute_GetTriggerMode(TriggerableObject);
		switch (TriggerMode)
		{
		case ETriggerMode::TM_Server:
			Server_ExecuteReleaseTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
			break;
		case ETriggerMode::TM_Client:
			Client_ExecuteReleaseTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
			break;
		case ETriggerMode::TM_Multicast:
			Server_MulticastExecuteReleaseTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
			break;
		}
	}
}


void UObjectTriggererComponent::Server_ExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_Trigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

void UObjectTriggererComponent::Client_ExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_Trigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

void UObjectTriggererComponent::Server_MulticastExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	UObjectTriggererComponent* Triggerer = GlobalObjectTriggerer;
	if (!IsValid(Triggerer))
		Triggerer = this;
	Triggerer->NetMulticast_ExecuteTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

void UObjectTriggererComponent::NetMulticast_ExecuteTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_Trigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

void UObjectTriggererComponent::Server_ExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_ReleaseTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

void UObjectTriggererComponent::Client_ExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_ReleaseTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

void UObjectTriggererComponent::Server_MulticastExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	UObjectTriggererComponent* Triggerer = GlobalObjectTriggerer;
	if (!IsValid(Triggerer))
		Triggerer = this;
	Triggerer->NetMulticast_ExecuteReleaseTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

void UObjectTriggererComponent::NetMulticast_ExecuteReleaseTrigger_Implementation(UObject* TriggerableObject, AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
	ITriggerable::Execute_ReleaseTrigger(TriggerableObject, TriggeringController, TriggeringPawn, Tag, Payload);
}

UObjectTriggererComponent* UObjectTriggererComponent::GetGlobalObjectTriggererComponent() const
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	UObjectTriggererComponent *GlobalTrigger = GameState->GetComponentByClass<UObjectTriggererComponent>();

	if (!IsValid(GlobalTrigger))
		UE_LOG(LogTemp, Warning, TEXT("No UObjectTriggererComponent in GameState... Multicast triggers won't be executed by everyone"));

	return GlobalTrigger;
}
