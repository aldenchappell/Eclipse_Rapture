// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/AmmoCounterWComponent.h"
#include "UI/AmmoCounter.h"
#include "Components/TextBlock.h" // Add this include

void UAmmoCounterWComponent::SetAmmoCounterText(int CurrentAmmo, int MaxAmmo)
{
	if (AmmoCounter == nullptr)
	{
		AmmoCounter = Cast<UAmmoCounter>(GetUserWidgetObject());
	}

	AmmoCounter->AmmoCounterText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentAmmo, MaxAmmo)));
}
