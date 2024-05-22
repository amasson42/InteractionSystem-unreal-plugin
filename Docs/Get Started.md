
## Setup Player Controller

1. Add InteractionControllerComponent to PlayerController
2. Set the Cursor Channel to a custom value

## Setup Game State

1. Add component `ObjectTriggerer` to the game state

## Interaction Widget

1. Inherit WBP_AInteractionSystemWidget
	1. Add a text in the Slot_InteractionButton
	2. Override the function InteractionButtonWillAppear
	3. Make it modify the text with the infos text
	4. Override the function InteractionButtonDidDisappear
	5. Make it clear the text
2. In the player controller, add on begin play the interaction widget

## Make an object hoverable

1. Create an actor
2. Add a static mesh to it
3. Make it implement interface WorldHoverable
4. Override functions from the interface to define its behavior
