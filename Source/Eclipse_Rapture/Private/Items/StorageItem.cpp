// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/StorageItem.h"
#include "Character/InventoryComponent.h"

AStorageItem::AStorageItem()
{
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lid Mesh"));
	LidMesh->SetupAttachment(ItemMesh);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}

void AStorageItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	Super::Interact_Implementation(Character);
}
