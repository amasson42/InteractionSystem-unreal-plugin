// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionSystemWidget.generated.h"

// TODO: Move everything from the widget blueprint to this class

/**
 * 
 */
UCLASS(Abstract)
class INTERACTIONSYSTEM_API UInteractionSystemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = true))
    class UInteractionControllerComponent* InteractionControllerComponent;

    UPROPERTY(BlueprintReadWrite)
    TObjectPtr<UObject> HoveredObject;
};
