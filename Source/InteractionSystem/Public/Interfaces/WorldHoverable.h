// Amasson

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WorldHoverable.generated.h"


USTRUCT(BlueprintType)
struct INTERACTIONSYSTEM_API FWorldHoverableInfos
{
    GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location = FVector::ZeroVector;

	/** Is Location in Screen Space or World Space */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bScreenSpace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Payload = nullptr;

};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWorldHoverable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIONSYSTEM_API IWorldHoverable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WorldTooltip")
	void GetWorldHoverableInfos(FWorldHoverableInfos& Infos);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WorldTooltip")
	bool CanBeHovered(AController* Controller, const FHitResult& TraceHit);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WorldTooltip")
	void HoveredBegin(AController* Controller, const FHitResult& TraceHit);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "WorldTooltip")
	void HoveredEnd(AController* Controller);

};
