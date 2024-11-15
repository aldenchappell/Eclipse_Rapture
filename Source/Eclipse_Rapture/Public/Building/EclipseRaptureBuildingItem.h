// EclipseRaptureBuildingItem.h

#pragma once

#include "Interfaces/CoverObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EclipseRaptureBuildingItem.generated.h"

UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureBuildingItem : public AActor, public ICoverObject
{
    GENERATED_BODY()

public:
    AEclipseRaptureBuildingItem();

protected:
    virtual void BeginPlay() override;

    void InitCoverPoints();

    // Implementations of the interface methods
    virtual void SetCoverPoints_Implementation(const TArray<class AActor*>& NewCoverPoints) override;
    virtual TArray<AActor*> GetCoverPoints_Implementation() override;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Building | Cover")
    int32 CoverPointsCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building | Cover")
    TArray<AActor*> CoverPoints;
};
