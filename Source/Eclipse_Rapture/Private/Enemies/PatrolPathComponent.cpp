// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/PatrolPathComponent.h"

// Sets default values for this component's properties
UPatrolPathComponent::UPatrolPathComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

FVector UPatrolPathComponent::GetWaypointLocation(int32 Index) const
{
	if (PatrolPoints.IsValidIndex(Index))
	{
		return PatrolPoints[Index]->GetActorLocation();
	}
	return FVector::ZeroVector;
}

int32 UPatrolPathComponent::GetNextWaypointIndex(int32 CurrentIndex) const
{
	if (bEnableRandomPointPathfinding)
	{
		return FMath::RandRange(0, PatrolPoints.Num() - 1);
	}
	else
	{
		CurrentIndex++;
		if (CurrentIndex >= PatrolPoints.Num())
		{
			CurrentIndex = 0;
		}
	}
	return CurrentIndex;
}

void UPatrolPathComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


