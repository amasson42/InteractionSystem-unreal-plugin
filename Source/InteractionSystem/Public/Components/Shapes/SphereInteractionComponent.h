// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Interfaces/WorldHoverable.h"
#include "Interfaces/Triggerable.h"
#include "SphereInteractionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSphereInteractionHoverBeginSignature, USphereInteractionComponent*, SphereInteraction, FHitResult, CursorHit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSphereInteractionHoverEndSignature, USphereInteractionComponent*, SphereInteraction);

/**
 * 
 */

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSYSTEM_API USphereInteractionComponent : public USphereComponent, public IWorldHoverable, public ITriggerable
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnSphereInteractionHoverBeginSignature OnHoverBegin;

	UPROPERTY(BlueprintAssignable)
	FOnSphereInteractionHoverEndSignature OnHoverEnd;

	/** Trigger */

	virtual void Trigger_Implementation(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload) override;
	virtual void ReleaseTrigger_Implementation(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload) override;
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
