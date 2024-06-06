// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Triggerable.generated.h"


UENUM(BlueprintType)
enum class ETriggerMode : uint8
{
	TM_Multicast	UMETA(DisplayName="Multicast"),
	TM_Server		UMETA(DisplayName="Server"),
	TM_Client		UMETA(DisplayName="Client"),
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTriggerable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIONSYSTEM_API ITriggerable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Triggerable")
	void Trigger(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Triggerable")
	void ReleaseTrigger(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Triggerable")
	ETriggerMode GetTriggerMode() const;

};
