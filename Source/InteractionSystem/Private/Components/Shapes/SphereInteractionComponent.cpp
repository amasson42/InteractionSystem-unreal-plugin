// Amasson


#include "Components/Shapes/SphereInteractionComponent.h"

/** Trigger */

void USphereInteractionComponent::Trigger_Implementation(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
    if (IsValid(TriggerTargetActor) && TriggerTargetActor->Implements<UTriggerable>())
    {
        ITriggerable::Execute_Trigger(TriggerTargetActor, TriggererController, Triggerer, this->TriggerTag, this->TriggerPayload);
    }
}

void USphereInteractionComponent::ReleaseTrigger_Implementation(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
    if (IsValid(TriggerTargetActor) && TriggerTargetActor->Implements<UTriggerable>())
    {
        ITriggerable::Execute_ReleaseTrigger(TriggerTargetActor, TriggererController, Triggerer, this->TriggerTag, this->TriggerPayload);
    }
}

ETriggerMode USphereInteractionComponent::GetTriggerMode_Implementation() const
{
    if (IsValid(TriggerTargetActor) && TriggerTargetActor->Implements<UTriggerable>())
    {
        return ITriggerable::Execute_GetTriggerMode(TriggerTargetActor);
    }
    return ETriggerMode::TM_Client;
}


/** Hovering */

void USphereInteractionComponent::GetWorldHoverableInfos_Implementation(FWorldHoverableInfos& Infos)
{
    Infos.Location = GetComponentTransform().TransformPosition(InfoLocationOffset);
    Infos.Text = InfoText;
    Infos.bScreenSpace = false;
}

bool USphereInteractionComponent::CanBeHovered_Implementation(AController* Controller, const FHitResult& TraceHit)
{
    if (MaxRange >= 0)
        return TraceHit.Distance < MaxRange;
    return true;
}

void USphereInteractionComponent::HoveredBegin_Implementation(AController* Controller, const FHitResult& TraceHit)
{
    OnHoverBegin.Broadcast(this, TraceHit);
}

void USphereInteractionComponent::HoveredEnd_Implementation(AController* Controller)
{
    OnHoverEnd.Broadcast(this);
}
