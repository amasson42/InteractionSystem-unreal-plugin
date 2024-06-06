// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Interfaces/WorldHoverable.h"
#include "Interfaces/Triggerable.h"
#include "BoxInteractionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionHoverBeginSignature, UBoxInteractionComponent*, BoxInteraction, FHitResult, CursorHit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionHoverEndSignature, UBoxInteractionComponent*, BoxInteraction);

/**
 * 
 */

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSYSTEM_API UBoxInteractionComponent : public UBoxComponent, public IWorldHoverable, public ITriggerable
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnInteractionHoverBeginSignature OnHoverBegin;

	UPROPERTY(BlueprintAssignable)
	FOnInteractionHoverEndSignature OnHoverEnd;

	/** Trigger */

	virtual void Trigger_Implementation(AController* TriggeringController, AActor* TriggeringActor, FName Tag, UObject* Payload) override;
	virtual void ReleaseTrigger_Implementation(AController* TriggeringController, AActor* TriggeringActor, FName Tag, UObject* Payload) override;
	virtual ETriggerMode GetTriggerMode_Implementation() const override;


	/** Hovering */

	virtual void GetWorldHoverableInfos_Implementation(FWorldHoverableInfos& Infos) override;
	virtual bool CanBeHovered_Implementation(AController* Controller, const FHitResult& TraceHit) override;
	virtual void HoveredBegin_Implementation(AController* Controller, const FHitResult& TraceHit) override;
	virtual void HoveredEnd_Implementation(AController* Controller) override;


	/** Trigger Properties */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TObjectPtr<AActor> TriggerTargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FName TriggerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TObjectPtr<UObject> TriggerPayload;


	/** Hovering Properties */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float MaxRange = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FVector InfoLocationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InfoText;
	

};
