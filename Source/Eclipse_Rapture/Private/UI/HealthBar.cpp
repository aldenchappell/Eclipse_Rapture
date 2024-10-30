#include "UI/HealthBar.h"
#include "Components/ProgressBar.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Global/Components/HealthComponent.h"

// NativeConstruct: Called when the widget is constructed
void UHealthBar::NativeConstruct()
{
    AEclipseRaptureCharacter* Player = Cast<AEclipseRaptureCharacter>(GetOwningPlayerPawn());
    if (Player && Player->HealthComponent)
    {
        // Bind the OnHealthUpdated delegate to the SetHealthPercent function
        Player->HealthComponent->OnHealthUpdated.AddDynamic(this, &UHealthBar::SetHealthPercent);
    }
}

// Set the health percentage on the progress bar
void UHealthBar::SetHealthPercent(float Percent)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(Percent);
        UE_LOG(LogTemp, Warning, TEXT("Health Percent Updated: %f"), Percent);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HealthBar widget is not bound!"));
    }
}
