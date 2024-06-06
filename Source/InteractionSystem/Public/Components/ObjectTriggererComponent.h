// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectTriggererComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSYSTEM_API UObjectTriggererComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UObjectTriggererComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Trigger")
	void ExecuteTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(BlueprintCallable, Category = "Trigger")
	void ExecuteReleaseTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

protected:

	UFUNCTION(Server, Reliable)
	void Server_ExecuteTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(Client, Reliable)
	void Client_ExecuteTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(Server, Reliable)
	void Server_MulticastExecuteTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_ExecuteTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(Server, Reliable)
	void Server_ExecuteReleaseTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(Client, Reliable)
	void Client_ExecuteReleaseTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(Server, Reliable)
	void Server_MulticastExecuteReleaseTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_ExecuteReleaseTrigger(UObject* TriggerableObject, AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);


	UObjectTriggererComponent* GetGlobalObjectTriggererComponent() const;

	UPROPERTY()
	TObjectPtr<UObjectTriggererComponent> GlobalObjectTriggerer;

};
