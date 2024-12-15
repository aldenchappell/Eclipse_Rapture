// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/AmmoItem.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Character/InventoryComponent.h"

AAmmoItem::AAmmoItem()
{
	
}

void AAmmoItem::BeginPlay()
{
	InitializeAmmoDrop();
}

void AAmmoItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AAmmoItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AAmmoItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	if (PlayerReference)
	{
		if (OwningInventory)
		{
			//Add AmmoDropAmount of ammo to the player's inventory
			OwningInventory->AddItemAmount(GetClass(), AmmoDropAmount);
		}
		Destroy();
	}
}

void AAmmoItem::Use(AEclipseRaptureCharacter* Character)
{

}

void AAmmoItem::InitializeAmmoDrop()
{
	AmmoDropAmount = FMath::RandRange(MinAmount, MaxAmount);

	UE_LOG(LogTemp, Warning, TEXT("Ammo Amount: %d"), AmmoDropAmount);
}
