
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
    OwningCharacter = Cast<AEclipseRaptureCharacter>(GetOwner());
    if (!OwningCharacter)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Building Component must be attached to an EclipseRaptureCharacter"));
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
    }
}

void UBuildingComponent::BuildingBlueprintLineTrace_Implementation()
{
 //   UE_LOG(LogTemp, Warning, TEXT("BuildingBlueprintLineTrace_Implementation called on %s"), *GetName());

 //   // Check preconditions
 //   if (!OwningCharacter)
 //   {
 //       UE_LOG(LogTemp, Warning, TEXT("Precondition failed: OwningCharacter is NULL"));
 //       return;
 //   }
 //   if (!OwningCharacter->bHasBuildingBlueprint)
 //   {
 //       UE_LOG(LogTemp, Warning, TEXT("Precondition failed: bHasBuildingBlueprint is FALSE"));
 //       return;
 //   }
 //   if (!OwningCharacter->bBuildingBlueprintEquipped)
 //   {
 //       UE_LOG(LogTemp, Warning, TEXT("Precondition failed: bBuildingBlueprintEquipped is FALSE"));
 //       return;
 //   }

 //   // Perform the line trace
 //   FVector TraceStart = OwningCharacter->GetActorLocation() + FVector(0.f, 0.f, 50.f);
 //   FVector TraceEnd = TraceStart + OwningCharacter->GetActorForwardVector() * BuildingTraceLength;

 //   bool bDetectedActor = GetWorld()->LineTraceSingleByChannel(
 //       LastHitResult,
 //       TraceStart,
 //       TraceEnd,
 //       ECollisionChannel::ECC_Visibility,
 //       FCollisionQueryParams(FName(TEXT("BuildingBlueprintTrace")), false, OwningCharacter)
 //   );

 //   // Draw the debug line
 //   DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.f, 0, 2.f);
 //   UE_LOG(LogTemp, Warning, TEXT("Trace Start: %s | Trace End: %s"),
 //          *TraceStart.ToString(), *TraceEnd.ToString());

 //   //Set the reference to the hitresult from interface function
	//IBuilderInterface::Execute_GetBuildingBlueprintHitResult(this);

 //   // Handle hit result
 //   if (bDetectedActor)
 //   {
 //       DrawDebugSphere(GetWorld(), LastHitResult.ImpactPoint, 10.f, 12, FColor::Green, false, 1.f);
 //       UE_LOG(LogTemp, Warning, TEXT("LINE TRACE HIT: %s"), *LastHitResult.GetActor()->GetName());

 //       AActor* HitActor = LastHitResult.GetActor();
 //       if (HitActor && HitActor->Implements<UBuildingInterface>())
 //       {
 //           UE_LOG(LogTemp, Warning, TEXT("Actor Implements UBuildingInterface"));
 //           AEclipseRaptureBuildingItem* BuildingItem = IBuildingInterface::Execute_GetBuildingItem(HitActor);
 //           if (BuildingItem)
 //           {
 //               //UE_LOG(LogTemp, Warning, TEXT("Building Item Found: %s"), *BuildingItem->GetName());
 //               IBuilderInterface::Execute_SetBuildingItemBeingLookedAt(this, BuildingItem);
 //           }
 //       }
 //       else
 //       {
 //           UE_LOG(LogTemp, Warning, TEXT("Actor does not implement UBuildingInterface"));
 //           IBuilderInterface::Execute_SetBuildingItemBeingLookedAt(this, nullptr);
 //       }
 //   }
 //   else
 //   {
 //       //UE_LOG(LogTemp, Warning, TEXT("No actor hit in line trace"));
 //       IBuilderInterface::Execute_SetBuildingItemBeingLookedAt(this, nullptr);
 //   }
}

void UBuildingComponent::SetBuildingItemBeingLookedAt_Implementation(AEclipseRaptureBuildingItem* BuildingItem)
{
    CurrentBuildingItem = BuildingItem;
}

AEclipseRaptureBuildingItem* UBuildingComponent::GetBuildingItemBeingLookedAt_Implementation()
{
    return CurrentBuildingItem;
}

void UBuildingComponent::SetBuildingHitLocation_Implementation(FVector HitLocation)
{
    BuildingHitLocation = HitLocation;
}

FVector UBuildingComponent::GetBuildingHitLocation_Implementation()
{
    return BuildingHitLocation;
}

FHitResult UBuildingComponent::GetBuildingBlueprintHitResult_Implementation()
{
    return LastHitResult;
}