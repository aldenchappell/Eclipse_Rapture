#include "Enemies/PatrolPathComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Enemies/PatrolPoint.h"

// Sets default values for this component's properties
UPatrolPathComponent::UPatrolPathComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPatrolPathComponent::BeginPlay()
{
    Super::BeginPlay();

    if (PatrolPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("PatrolPathComponent: No patrol points assigned!"));
    }
}

FVector UPatrolPathComponent::GetWaypointLocation(int32 Index) const
{
    // Ensure the index is valid and the patrol point exists
    if (PatrolPoints.IsValidIndex(Index) && PatrolPoints[Index] != nullptr)
    {
        return PatrolPoints[Index]->GetActorLocation();
    }

    return FVector::ZeroVector;
}

int32 UPatrolPathComponent::GetNextWaypointIndex()
{
    if (bEnableRandomPointPathfinding)
    {
        // Return a random index
        return FMath::RandRange(0, PatrolPoints.Num() - 1);
    }
    else
    {
        // Increment and wrap around the patrol point index
        CurrentPatrolPointIndex = (CurrentPatrolPointIndex + 1) % PatrolPoints.Num();
        return CurrentPatrolPointIndex;
    }
}
