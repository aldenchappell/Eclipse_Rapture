// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Interfaces/IPhysicsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Items/ItemObject.h"

UItemObject::UItemObject()
{
	ItemWeight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");

}


void UItemObject::Rotate_Implementation()
{
}

FInventorySpaceRequirements UItemObject::GetInventorySpaceRequirements_Implementation()
{
	return InventorySpaceRequired;
}

void UItemObject::InitializeItemAmount_Implementation()
{
	ItemAmount = FMath::RandRange(MinItemDropAmount, MaxItemDropAmount);
}

void UItemObject::SetIsRotated(bool bNewIsRotated)
{
	bRotated = bNewIsRotated;
}

UMaterialInterface* UItemObject::GetItemIcon_Implementation() const
{
	return nullptr;
}
