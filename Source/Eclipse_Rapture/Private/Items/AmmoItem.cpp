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
