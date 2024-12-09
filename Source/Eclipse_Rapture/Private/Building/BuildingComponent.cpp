#include "Building/BuildingComponent.h"
#include "Interfaces/BuildingInterface.h"
#include "Character/EclipseRaptureCharacter.h"

UBuildingComponent::UBuildingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

	BlueprintMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blueprint Mesh"));
	BlueprintMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UBuildingComponent::BeginPlay()
{
    Super::BeginPlay();
    OwningCharacter = Cast<AEclipseRaptureCharacter>(GetOwner());
    if (!OwningCharacter)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Building Component must be attached to an EclipseRaptureCharacter"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("OwningCharacter set to: %s"), *OwningCharacter->GetName());
    }
}


bool UBuildingComponent::HasBuildingBlueprint_Implementation()
{
    if (OwningCharacter)
    {
        return OwningCharacter->bHasBuildingBlueprint;
    }
    return false;
}

bool UBuildingComponent::GetHasBuildingBlueprintEquipped_Implementation()
{
    if (OwningCharacter)
    {
		return OwningCharacter->bBuildingBlueprintEquipped;
    }
    return false;
}

void UBuildingComponent::SetHasBuildingBlueprint_Implementation(bool NewHasBlueprint)
{
    if (OwningCharacter)
    {
        OwningCharacter->bHasBuildingBlueprint = NewHasBlueprint;
        UE_LOG(LogTemp, Warning, TEXT("bHasBuildingBlueprint set to %s"), NewHasBlueprint ? TEXT("true") : TEXT("false"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("OwningCharacter is null in SetHasBuildingBlueprint."));
    }
}


void UBuildingComponent::BuildingBlueprintLineTrace_Implementation()
{
    if (!OwningCharacter || !OwningCharacter->bHasBuildingBlueprint || !OwningCharacter->bBuildingBlueprintEquipped)
        return;

    FVector TraceStart = OwningCharacter->GetActorLocation() + FVector(0.f, 0.f, 50.f);
    FVector TraceEnd = TraceStart + OwningCharacter->GetActorForwardVector() * BuildingTraceLength;

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
