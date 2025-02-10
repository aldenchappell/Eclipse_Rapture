#pragma once

#include "Character/EclipseRaptureCharacter.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(Blueprintable)
class UInteractInterface : public UInterface
{
    GENERATED_BODY()
};

class ECLIPSE_RAPTURE_API IInteractInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Interact(AEclipseRaptureCharacter* Character);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Use(AEclipseRaptureCharacter* Character);
};
