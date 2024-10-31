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
			for (int AmountToAdd = 0; AmountToAdd < Amount; AmountToAdd++)
			{
				OwningInventory->AddItem(this);
			}
		}
	}
}

void AAmmoItem::Use(AEclipseRaptureCharacter* Character)
{
	//update weapon ammo UI
}

void AAmmoItem::InitializeAmmoDrop()
{
	Amount = FMath::RandRange(MinAmount, MaxAmount);

	UE_LOG(LogTemp, Warning, TEXT("Ammo Amount: %d"), Amount);
}
