#include "Building/BuildingComponent.h"
#include "Interfaces/BuildingInterface.h"
#include "Character/EclipseRaptureCharacter.h"

UBuildingComponent::UBuildingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UBuildingComponent::BeginPlay()
{
    Super::BeginPlay();
}

bool UBuildingComponent::HasBuildingBlueprint_Implementation()
{
    AEclipseRaptureCharacter* Character = Cast<AEclipseRaptureCharacter>(GetOwner());
    if (Character)
    {
        return Character->bHasBuildingBlueprint;
    }
    return false;
}

void UBuildingComponent::SetHasBuildingBlueprint_Implementation(bool NewHasBlueprint)
{
    AEclipseRaptureCharacter* Character = Cast<AEclipseRaptureCharacter>(GetOwner());
    if (Character)
    {
        Character->bHasBuildingBlueprint = NewHasBlueprint;
    }
}

void UBuildingComponent::BuildingBlueprintLineTrace_Implementation()
{
    AEclipseRaptureCharacter* Character = Cast<AEclipseRaptureCharacter>(GetOwner());
    if (!Character || !Character->bHasBuildingBlueprint)
        return;

    FVector TraceStart = Character->GetActorLocation() + FVector(0.f, 0.f, 50.f);
    FVector TraceEnd = TraceStart + Character->GetActorForwardVector() * BuildingTraceLength;

    FHitResult HitResult;
    bool bDetectedActor = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECollisionChannel::ECC_Visibility,
        FCollisionQueryParams::DefaultQueryParam
    );

    if (bDetectedActor)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->Implements<UBuildingInterface>())
        {
            AEclipseRaptureBuildingItem* BuildingItem = IBuildingInterface::Execute_GetBuildingItem(HitActor);
            if (BuildingItem)
            {
                IBuilderInterface::Execute_SetBuildingItemBeingLookedAt(this, BuildingItem);
            }
        }
        else
        {
            IBuilderInterface::Execute_SetBuildingItemBeingLookedAt(this, nullptr);
        }
    }
    else
    {
        IBuilderInterface::Execute_SetBuildingItemBeingLookedAt(this, nullptr);
    }
}


void UBuildingComponent::SetBuildingItemBeingLookedAt_Implementation(AEclipseRaptureBuildingItem* BuildingItem)
{
    CurrentBuildingItem = BuildingItem;
}
