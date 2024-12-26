#include "Items/Item_Blueprint.h"
#include "Building/BuildingComponent.h"
#include "Interfaces/BuilderInterface.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Character/InventoryComponent.h"

AItem_Blueprint::AItem_Blueprint()
{
    bCanBeUsed = false;
}

void AItem_Blueprint::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
    if (Character)
    {
        Super::Execute_Interact(this, Character);
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
