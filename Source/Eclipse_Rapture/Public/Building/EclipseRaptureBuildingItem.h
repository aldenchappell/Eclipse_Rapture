// EclipseRaptureBuildingItem.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EclipseRaptureBuildingItem.generated.h"

UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureBuildingItem : public AActor
{
    GENERATED_BODY()

public:
    AEclipseRaptureBuildingItem();

protected:
    virtual void BeginPlay() override;


};
