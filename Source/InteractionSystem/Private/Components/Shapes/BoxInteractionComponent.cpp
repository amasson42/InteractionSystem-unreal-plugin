// Amasson


#include "Components/Shapes/BoxInteractionComponent.h"

/** Trigger */

void UBoxInteractionComponent::Trigger_Implementation(AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
    if (IsValid(TriggeringActor) && TriggeringActor->Implements<UTriggerable>())
    {
        ITriggerable::Execute_Trigger(TriggeringActor, TriggeringController, TriggeringPawn, this->TriggeringTag, this->TriggeringPayload);
    }
}

void UBoxInteractionComponent::ReleaseTrigger_Implementation(AController* TriggeringController, APawn* TriggeringPawn, FName Tag, UObject* Payload)
{
    if (IsValid(TriggeringActor) && TriggeringActor->Implements<UTriggerable>())
    {
        ITriggerable::Execute_ReleaseTrigger(TriggeringActor, TriggeringController, TriggeringPawn, this->TriggeringTag, this->TriggeringPayload);
    }
}

ETriggerMode UBoxInteractionComponent::GetTriggerMode_Implementation() const
{
    if (IsValid(TriggeringActor) && TriggeringActor->Implements<UTriggerable>())
    {
        return ITriggerable::Execute_GetTriggerMode(TriggeringActor);
    }
    return ETriggerMode::TM_Client;
}


/** Hovering */

void UBoxInteractionComponent::GetWorldHoverableInfos_Implementation(FWorldHoverableInfos& Infos)
{
    Infos.Location = GetComponentTransform().TransformPosition(InfoLocationOffset);
    Infos.Text = InfoText;
    Infos.bScreenSpace = false;
}

bool UBoxInteractionComponent::CanBeHovered_Implementation(AController* Controller, const FHitResult& TraceHit)
{
    if (MaxRange >= 0)
        return TraceHit.Distance < MaxRange;
    return true;
}

void UBoxInteractionComponent::HoveredBegin_Implementation(AController* Controller, const FHitResult& TraceHit)
{
    OnHoverBegin.Broadcast(this, TraceHit);
}

void UBoxInteractionComponent::HoveredEnd_Implementation(AController* Controller)
{
    OnHoverEnd.Broadcast(this);
}
