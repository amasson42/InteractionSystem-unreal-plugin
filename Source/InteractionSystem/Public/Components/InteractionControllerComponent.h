// Amasson

#pragma once

#include "CoreMinimal.h"
#include "Components/ObjectTriggererComponent.h"
#include "Interfaces/WorldHoverable.h"
#include "Interfaces/Triggerable.h"
#include "InteractionControllerComponent.generated.h"

class APlayerController;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHoverObjectChangedSignature, UInteractionControllerComponent*, InteractionComponent, UObject*, WorldHoverable);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INTERACTIONSYSTEM_API UInteractionControllerComponent : public UObjectTriggererComponent
{
	GENERATED_BODY()

public:

	UInteractionControllerComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Hover")
	FOnHoverObjectChangedSignature OnHoverObjectBegin;

	UPROPERTY(BlueprintAssignable, Category = "Hover")
	FOnHoverObjectChangedSignature OnHoverObjectEnd;

	UFUNCTION(BlueprintCallable, Category = "Hover")
	FORCEINLINE UObject* GetHoveredObject() const { return HoveredObject.Get(); }

	UFUNCTION(BlueprintCallable, Category = "Hover")
	FORCEINLINE AActor* GetHoveredActor() const { return HoveredObject.IsValid() ? Cast<AActor>(HoveredObject.Get()) : nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Hover")
	FORCEINLINE UActorComponent* GetHoveredComponent() const { return HoveredObject.IsValid() ? Cast<UActorComponent>(HoveredObject.Get()) : nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Cursor")
	const FHitResult& GetCursorHit() const { return CursorHit; }

	UFUNCTION(BlueprintCallable, Category = "Trigger")
	void TriggerHoveredObject();

	UFUNCTION(BlueprintCallable, Category = "Trigger")
	void ReleaseTriggerHoveredObject();

	UFUNCTION(BlueprintCallable, Category = "Trigger")
    void TriggerObject(UObject* TriggerableObject, FName Tag, UObject* Payload);

	UFUNCTION(BlueprintCallable, Category = "Trigger")
    void ReleaseTriggerObject(UObject* TriggerableObject, FName Tag, UObject* Payload);

	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;

protected:

	void UpdateHover();

	UObject* GetHoverableObjectFromCursorHit();
	void UnhoverObject_Unsafe();
	void HoverObject(UObject* NewHoverObject);

	UPROPERTY()
	TObjectPtr<APlayerController> OwningPlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cursor", meta = (AllowPrivateAccess = true))
	TEnumAsByte<ECollisionChannel> CursorChannel;

	UPROPERTY()
	FHitResult CursorHit;

	UPROPERTY()
	TWeakObjectPtr<UObject> HoveredObject;

	// UPROPERTY(EditAnywhere, Category = "Cursor", meta = (AllowPrivateAccess = true))
	// TObjectPtr<UInputAction> InteractionInput;

	bool bHoveredObjectPressed = false;

};
