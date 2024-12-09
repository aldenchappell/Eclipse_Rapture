#include "Items/Item_Blueprint.h"
#include "Building/BuildingComponent.h"
#include "Interfaces/BuilderInterface.h"
#include "Character/EclipseRaptureCharacter.h"

AItem_Blueprint::AItem_Blueprint()
{
    ItemDisplayName = FText::FromString("Blueprint");
    ItemDescription = FText::FromString("A blueprint for building.");
    ItemWeight = 0.1f;
    UseActionText = FText::FromString("Pick up building blueprint");
    bCanBeUsed = false;
}

void AItem_Blueprint::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
    if (Character && Character == OverlappingCharacter)
    {
        UBuildingComponent* BuildingComp = Character->FindComponentByClass<UBuildingComponent>();
        if (BuildingComp && BuildingComp->GetClass()->ImplementsInterface(UBuilderInterface::StaticClass()))
        {
            // Correctly pass the object that implements the interface
            IBuilderInterface::Execute_SetHasBuildingBlueprint(BuildingComp, true);
            UE_LOG(LogTemp, Warning, TEXT("Player picked up building blueprint."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("BuildingComponent not found or does not implement IBuilderInterface!"));
        }
    }
}

void AItem_Blueprint::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

    OverlappingCharacter = Cast<AEclipseRaptureCharacter>(OtherActor);
    UE_LOG(LogTemp, Warning, TEXT("Overlapping with building blueprint."));
}

void AItem_Blueprint::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                         int32 OtherBodyIndex)
{
    Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

    OverlappingCharacter = nullptr;
}
