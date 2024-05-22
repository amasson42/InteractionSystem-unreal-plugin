// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Interfaces/WorldHoverable.h"
#include "InteractionSystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class INTERACTIONSYSTEM_API UInteractionSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "WorldTooltip", meta = (DefaultToSelf = "Actor"))
	static void DefaultsActorWorldHoverableInfos(AActor* Actor, FText TooltipText, FWorldHoverableInfos& Infos);

};
