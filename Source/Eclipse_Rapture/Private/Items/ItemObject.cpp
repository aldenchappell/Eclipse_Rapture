// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Interfaces/IPhysicsComponent.h"
#include "Items/ItemObject.h"

UItemObject::UItemObject()
{
	ItemWeight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

FInventoryDimensions UItemObject::GetInventoryDimensions()
{
	if (bRotated)
	{
		return InventoryDimensions;
	}
	else
	{
		return FInventoryDimensions(InventoryDimensions.DimensionsY, InventoryDimensions.DimensionsX);
	}
}

UMaterialInterface* UItemObject::GetItemIcon() const
{
	if (!ItemIcon || !ItemIconRotated) return nullptr;

	return bRotated ? ItemIconRotated : ItemIcon;
}

void UItemObject::Rotate()
{
	bRotated = !bRotated;
}