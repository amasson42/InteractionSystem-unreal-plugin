// Amasson


#include "InteractionSystemLibrary.h"

void UInteractionSystemLibrary::DefaultsActorWorldHoverableInfos(AActor* Actor, FText TooltipText, FWorldHoverableInfos& Infos)
{
    Infos.Location = IsValid(Actor) ? Actor->GetActorLocation() : FVector();
    Infos.Text = TooltipText;
    Infos.bScreenSpace = false;
}
