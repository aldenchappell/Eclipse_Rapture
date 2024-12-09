#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolPathComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UPatrolPathComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPatrolPathComponent();

    // If true, ignores patrol points and uses random points
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Points")
    bool bEnableRandomPointPathfinding = false;

    // Patrol points as scene components
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol Points")
    TArray<class APatrolPoint*> PatrolPoints;

    // Gets the location of the patrol point at a specific index
    UFUNCTION(BlueprintCallable, Category = "Patrol Points")
    FVector GetWaypointLocation(int32 Index) const;

    // Gets the next waypoint index based on the current logic
    UFUNCTION(BlueprintCallable, Category = "Patrol Points")
    int32 GetNextWaypointIndex();

protected:
    virtual void BeginPlay() override;

private:
    int32 CurrentPatrolPointIndex = 0;
};
