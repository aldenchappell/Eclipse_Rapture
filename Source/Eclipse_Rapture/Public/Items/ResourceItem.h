// ResourceItem.h
#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "ResourceItem.generated.h"

UCLASS()
class ECLIPSE_RAPTURE_API AResourceItem : public AItem
{
    GENERATED_BODY()

public:
    AResourceItem();

    virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;

protected:
    virtual void Use(AEclipseRaptureCharacter* Character) override;
};
