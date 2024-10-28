// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FoodItem.h"
#include "Global/Components/HealthComponent.h"


void AFoodItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{

}

AFoodItem::AFoodItem()
{

}

void AFoodItem::Use(AEclipseRaptureCharacter* Character)
{
	if (Character && Character->GetHealthComponent())
	{
		Character->GetHealthComponent()->HealSatiety(FoodSatietyHealAmount);
	}
}