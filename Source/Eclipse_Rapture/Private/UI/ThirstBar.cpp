// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ThirstBar.h"
#include "Components/ProgressBar.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Global/Components/HealthComponent.h"

void UThirstBar::NativeConstruct()
{
	AEclipseRaptureCharacter* Player = Cast<AEclipseRaptureCharacter>(GetOwningPlayerPawn());
	if (Player && Player->HealthComponent)
	{
		// Bind the OnHealthUpdated delegate to the SetHealthPercent function
		Player->HealthComponent->OnThirstUpdated.AddDynamic(this, &UThirstBar::SetThirstPercent);
	}

	SetThirstPercent(Player->HealthComponent->MaxThirst);
}

void UThirstBar::SetThirstPercent(float Percent)
{
	if (ThirstBar)
	{
		ThirstBar->SetPercent(Percent);
	}
}