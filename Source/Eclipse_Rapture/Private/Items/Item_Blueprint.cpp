// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/BuilderInterface.h"
#include "Items/Item_Blueprint.h"

AItem_Blueprint::AItem_Blueprint()
{
	ItemDisplayName = FText::FromString("Blueprint");
	ItemDescription = FText::FromString("A blueprint for building.");
	ItemWeight = 0.1f;
	UseActionText = FText::FromString("pick up building blueprint");
	bCanBeUsed = false;
}

void AItem_Blueprint::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	if (Character)
	{
		if (Character->Implements<UBuilderInterface>())
		{
			IBuilderInterface::Execute_SetHasBuildingBlueprint(Character, true);
			UE_LOG(LogTemp, Warning, TEXT("Player picked up building blueprint."));
		}
	}
}
