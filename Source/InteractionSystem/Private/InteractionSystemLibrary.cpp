// Amasson


#include "InteractionSystemLibrary.h"

void UInteractionSystemLibrary::DefaultsActorWorldHoverableInfos(AActor* Actor, FText TooltipText, FWorldHoverableInfos& Infos)
{
    Infos.Location = IsValid(Actor) ? Actor->GetActorLocation() : FVector();
    Infos.Text = TooltipText;
    Infos.bScreenSpace = false;
}

void UInteractionSystemLibrary::DefaultsComponentWorldHoverableInfos(UActorComponent* Component, FText TooltipText, FWorldHoverableInfos& Infos)
{
    if (IsValid(Component))
    {
        if (USceneComponent* SceneComponent = Cast<USceneComponent>(Component))
        {
            Infos.Location = SceneComponent->GetComponentLocation();
        }
        else if (AActor* Owner = Component->GetOwner())
        {
            Infos.Location = Owner->GetActorLocation();
        }
    }
    Infos.Text = TooltipText;
    Infos.bScreenSpace = false;
}
