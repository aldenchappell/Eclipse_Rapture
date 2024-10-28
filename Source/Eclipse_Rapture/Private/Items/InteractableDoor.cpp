// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InteractableDoor.h"


AInteractableDoor::AInteractableDoor()
{
	ItemType = EItemType::EIT_Interactable;
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

	UE_LOG(LogTemp, Warning, TEXT("Overlapping with door"));
}

void AInteractableDoor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AInteractableDoor::HandleDoorInteraction(bool Opened)
{
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

void AInteractableDoor::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	Super::Interact_Implementation(Character);

	if (bIsOpen)
	{
		HandleDoorInteraction(true);
	}
	else
	{
		HandleDoorInteraction(false);
	}
}
