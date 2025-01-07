// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InteractableDoor.h"
#include "Character/InventoryComponent.h"

AInteractableDoor::AInteractableDoor()
{
	bIsOpen = false;

	ItemMesh->SetSimulatePhysics(false);
}

void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();
}

void AInteractableDoor::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	OverlappingCharacter = Cast<AEclipseRaptureCharacter>(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("Overlapping with door"));
}

void AInteractableDoor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	OverlappingCharacter = nullptr;
}

void AInteractableDoor::HandleDoorInteraction(bool Opened)
{
	if (bIsLocked && OverlappingCharacter)
	{
		Execute_Unlock(this, OverlappingCharacter->GetInventoryComponent());
	}

	if (Opened)
	{
		bIsOpen = false;
		CloseDoor();
	}
	else
	{
		bIsOpen = true;
		OpenDoor();
	}
}

void AInteractableDoor::Unlock_Implementation(UInventoryComponent* CharacterInventory)
{
	if (!bIsLocked) return;

	/*if (!RequiredItemIDToUnlock.ItemID.IsEmpty())
	{
		TODO: Come back here and fix for new inventory system.
		if (CharacterInventory->CheckForItem(RequiredItemToOpen))
		{
			bIsLocked = false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("You need a key to unlock this door"));
		}
	}*/
	
}

void AInteractableDoor::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	Super::Interact_Implementation(Character);

	HandleDoorInteraction(bIsOpen);
}
