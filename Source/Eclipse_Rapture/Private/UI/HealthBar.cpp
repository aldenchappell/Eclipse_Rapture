#include "UI/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Global/Components/HealthComponent.h"

void UHealthBar::NativeConstruct()
{
    AEclipseRaptureCharacter* Player = Cast<AEclipseRaptureCharacter>(GetOwningPlayerPawn());
    if (Player && Player->HealthComponent)
    {
        // Bind the OnHealthUpdated delegate to the SetHealthPercent function
        Player->HealthComponent->OnHealthUpdated.AddDynamic(this, &UHealthBar::SetHealthPercent);
    }

    SetHealthPercent(Player->HealthComponent->MaxHealth);
}

void UHealthBar::SetHealthPercent(float Percent)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(Percent);
    }
}
