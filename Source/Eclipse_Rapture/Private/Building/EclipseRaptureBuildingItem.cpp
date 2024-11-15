// EclipseRaptureBuildingItem.cpp

#include "Building/EclipseRaptureBuildingItem.h"

AEclipseRaptureBuildingItem::AEclipseRaptureBuildingItem()
{
    PrimaryActorTick.bCanEverTick = false;

    CoverPointsCount = 2;  
    for (int i = 0; i < CoverPointsCount; i++)
    {
		CoverPoints.Add(CreateDefaultSubobject<AActor>(FName(*FString::Printf(TEXT("CoverPoint_%d"), i))));
		//CoverPoints[i] = CreateDefaultSubobject<AActor>(FName(*FString::Printf(TEXT("CoverPoint_%d"), i)));
    }

    InitCoverPoints();
}

void AEclipseRaptureBuildingItem::BeginPlay()
{
    Super::BeginPlay();

    InitCoverPoints();
}

void AEclipseRaptureBuildingItem::InitCoverPoints()
{
    for (int32 i = 0; i < CoverPointsCount; i++)
    {
        if (GetWorld())
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.bAllowDuringConstructionScript = true;
            SpawnParams.Owner = this;

            // Spawn an actor as a cover point, and add it to CoverPoints array
            AActor* NewCoverPoint = GetWorld()->SpawnActor<AActor>(GetActorLocation(), GetActorRotation(), SpawnParams);
            if (NewCoverPoint)
            {
                CoverPoints.Add(NewCoverPoint);
            }
        }
    }
}

void AEclipseRaptureBuildingItem::SetCoverPoints_Implementation(const TArray<AActor*>& NewCoverPoints)
{
    CoverPoints = NewCoverPoints;
}

TArray<AActor*> AEclipseRaptureBuildingItem::GetCoverPoints_Implementation()
{
    return CoverPoints;
}
