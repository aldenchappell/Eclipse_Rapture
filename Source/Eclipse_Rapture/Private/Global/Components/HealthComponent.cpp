#include "Global/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetCurrentHealth(MaxHealth);
    SetCurrentSatiety(MaxSatiety);
    SetCurrentThirst(MaxThirst);
}

void UHealthComponent::BeginPlay()
{
    
}

// Health Functions

float UHealthComponent::GetCurrentHealth() const
{
    return CurrentHealth;
}

void UHealthComponent::SetCurrentHealth(float Health)
{
    CurrentHealth = FMath::Clamp(Health, 0.0f, MaxHealth);
    float HealthPercent = CurrentHealth / MaxHealth;
    OnHealthUpdated.Broadcast(HealthPercent);
}

void UHealthComponent::HealHealth(float HealAmount)
{
    if (CurrentHealth < MaxHealth)
    {
        SetCurrentHealth(CurrentHealth + HealAmount);
    }
}

void UHealthComponent::TakeDamage_Implementation(float DamageAmount, FVector HitLocation)
{
    if (CurrentHealth > 0)
    {
        SetCurrentHealth(CurrentHealth - DamageAmount);

        if (CurrentHealth <= 0)
        {
            SetCurrentHealth(0);
            UE_LOG(LogTemp, Warning, TEXT("%s is now dead"), *GetOwner()->GetName());
        }
    }
}

// Satiety (Hunger) Functions

float UHealthComponent::GetCurrentSatiety() const
{
    return CurrentSatiety;
}

void UHealthComponent::SetCurrentSatiety(float Satiety)
{
    CurrentSatiety = FMath::Clamp(Satiety, 0.0f, MaxSatiety);
    float SatietyPercent = CurrentSatiety / MaxSatiety;
    OnSatietyUpdated.Broadcast(SatietyPercent);
}

void UHealthComponent::HealSatiety(float SatietyAmount)
{
    if (CurrentSatiety < MaxSatiety)
    {
        SetCurrentSatiety(CurrentSatiety + SatietyAmount);
    }
}

// Thirst Functions

float UHealthComponent::GetCurrentThirst() const
{
    return CurrentThirst;
}

void UHealthComponent::SetCurrentThirst(float Thirst)
{
    CurrentThirst = FMath::Clamp(Thirst, 0.0f, MaxThirst);
    float ThirstPercent = CurrentThirst / MaxThirst;
    OnThirstUpdated.Broadcast(ThirstPercent);
}

void UHealthComponent::HealThirst(float ThirstAmount)
{
    if (CurrentThirst < MaxThirst)
    {
        SetCurrentThirst(CurrentThirst + ThirstAmount);
    }
}