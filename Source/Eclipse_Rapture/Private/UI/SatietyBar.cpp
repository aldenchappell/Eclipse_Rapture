// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SatietyBar.h"
#include "Components/ProgressBar.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Global/Components/HealthComponent.h"

void USatietyBar::NativeConstruct()
{
    AEclipseRaptureCharacter* Player = Cast<AEclipseRaptureCharacter>(GetOwningPlayerPawn());
    if (Player && Player->HealthComponent)
    {
        // Bind the OnHealthUpdated delegate to the SetHealthPercent function
        Player->HealthComponent->OnSatietyUpdated.AddDynamic(this, &USatietyBar::SetSatietyPercent);
    }

    SetSatietyPercent(Player->HealthComponent->MaxHealth);
}

void USatietyBar::SetSatietyPercent(float Percent)
{
	if (SatietyBar)
	{
		SatietyBar->SetPercent(Percent);
	}
}
