// Amasson


#include "Components/Shapes/BoxInteractionComponent.h"

/** Trigger */

void UBoxInteractionComponent::Trigger_Implementation(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
    if (IsValid(TriggerTargetActor) && TriggerTargetActor->Implements<UTriggerable>())
    {
        ITriggerable::Execute_Trigger(TriggerTargetActor, TriggererController, Triggerer, this->TriggerTag, this->TriggerPayload);
    }
}

void UBoxInteractionComponent::ReleaseTrigger_Implementation(AController* TriggererController, UObject* Triggerer, FName Tag, UObject* Payload)
{
    if (IsValid(TriggerTargetActor) && TriggerTargetActor->Implements<UTriggerable>())
    {
        ITriggerable::Execute_ReleaseTrigger(TriggerTargetActor, TriggererController, Triggerer, this->TriggerTag, this->TriggerPayload);
    }
}

ETriggerMode UBoxInteractionComponent::GetTriggerMode_Implementation() const
{
    if (IsValid(TriggerTargetActor) && TriggerTargetActor->Implements<UTriggerable>())
    {
        return ITriggerable::Execute_GetTriggerMode(TriggerTargetActor);
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
