// Amasson


#include "Components/InteractionControllerComponent.h"
#include "GameFramework/PlayerController.h"


UInteractionControllerComponent::UInteractionControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInteractionControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerController = Cast<APlayerController>(GetOwner());

	if (!IsValid(OwningPlayerController))
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractionControllerComponent is not owned by a valid APlayerController"));
	}
}

void UInteractionControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateHover();
}

void UInteractionControllerComponent::TriggerHoveredObject()
{
	if (HoveredObject.IsValid())
	{
		bHoveredObjectPressed = true;
		APawn* TriggeringPawn = nullptr;
		if (IsValid(OwningPlayerController))
			TriggeringPawn = OwningPlayerController->GetPawn();

		Super::ExecuteTrigger(HoveredObject.Get(), OwningPlayerController, TriggeringPawn, FName("PlayerInteraction"), this);
	}
}

void UInteractionControllerComponent::ReleaseTriggerHoveredObject()
{
	bHoveredObjectPressed = false;
	if (HoveredObject.IsValid())
	{
		APawn* TriggeringPawn = nullptr;
		if (IsValid(OwningPlayerController))
			TriggeringPawn = OwningPlayerController->GetPawn();

		Super::ExecuteReleaseTrigger(HoveredObject.Get(), OwningPlayerController, TriggeringPawn, FName("PlayerInteraction"), this);
	}
}

void UInteractionControllerComponent::TriggerObject(UObject* TriggerableObject, FName Tag, UObject* Payload)
{
    APawn* TriggeringPawn = nullptr;
	if (IsValid(OwningPlayerController))
		TriggeringPawn = OwningPlayerController->GetPawn();

	Super::ExecuteTrigger(TriggerableObject, OwningPlayerController, TriggeringPawn, Tag, Payload);
}

void UInteractionControllerComponent::ReleaseTriggerObject(UObject* TriggerableObject, FName Tag, UObject* Payload)
{
    APawn* TriggeringPawn = nullptr;
    if (IsValid(OwningPlayerController))
        TriggeringPawn = OwningPlayerController->GetPawn();

    Super::ExecuteReleaseTrigger(TriggerableObject, OwningPlayerController, TriggeringPawn, Tag, Payload);
}

void UInteractionControllerComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	if (bReset)
		CursorHit = FHitResult();
	SetComponentTickEnabled(true);
}

void UInteractionControllerComponent::Deactivate()
{
	Super::Deactivate();

	if (HoveredObject.IsValid())
		UnhoverObject_Unsafe();
	SetComponentTickEnabled(false);
}

void UInteractionControllerComponent::UpdateHover()
{
	if (!IsValid(OwningPlayerController))
		return;

	OwningPlayerController->GetHitResultUnderCursor(CursorChannel, false, CursorHit);

	UObject* NewHitObject = GetHoverableObjectFromCursorHit();

	if (HoveredObject.IsValid())
	{
		bool bCurrentHoverIsStillValid = IWorldHoverable::Execute_CanBeHovered(HoveredObject.Get(), OwningPlayerController, CursorHit);

		bool bShouldUnhover = (!bCurrentHoverIsStillValid) || (NewHitObject != HoveredObject);
		if (bShouldUnhover)
			UnhoverObject_Unsafe();
	}

	if (!HoveredObject.IsValid() && IsValid(NewHitObject))
	{
		HoverObject(NewHitObject);
	}
}

UObject* UInteractionControllerComponent::GetHoverableObjectFromCursorHit()
{
	UPrimitiveComponent* HitComponent = CursorHit.GetComponent();
	if (IsValid(HitComponent) && HitComponent->Implements<UWorldHoverable>())
	{
		if (IWorldHoverable::Execute_CanBeHovered(HitComponent, OwningPlayerController, CursorHit))
			return HitComponent;
	}
	AActor* HitActor = CursorHit.GetActor();
	if (IsValid(HitActor) && HitActor->Implements<UWorldHoverable>())
	{
		if (IWorldHoverable::Execute_CanBeHovered(HitActor, OwningPlayerController, CursorHit))
			return HitActor;
	}
	return nullptr;
}

void UInteractionControllerComponent::UnhoverObject_Unsafe()
{
	if (bHoveredObjectPressed)
		ReleaseTriggerHoveredObject();

	IWorldHoverable::Execute_HoveredEnd(HoveredObject.Get(), OwningPlayerController);

	OnHoverObjectEnd.Broadcast(this, HoveredObject.Get());

	HoveredObject = nullptr;
}

void UInteractionControllerComponent::HoverObject(UObject* NewHoverObject)
{
	HoveredObject = NewHoverObject;

	IWorldHoverable::Execute_HoveredBegin(HoveredObject.Get(), OwningPlayerController, CursorHit);

	OnHoverObjectBegin.Broadcast(this, HoveredObject.Get());
}
