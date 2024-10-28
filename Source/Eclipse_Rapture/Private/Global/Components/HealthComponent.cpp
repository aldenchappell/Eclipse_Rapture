// HealthComponent.cpp

#include "Global/Components/HealthComponent.h"

// Constructor
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentHealth(MaxHealth);
}

// Implementation of the TakeDamage event
void UHealthComponent::TakeDamage_Implementation(float DamageAmount, FVector HitLocation)
{
	if (CurrentHealth > 0)
	{
		CurrentHealth -= DamageAmount;
		if (CurrentHealth <= 0)
		{
			CurrentHealth = 0;
			// Handle death logic here (if needed)
		}
	}
}

// Get current health value
float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

// Set current health value
void UHealthComponent::SetCurrentHealth(float Health)
{
	CurrentHealth = Health;
}

// Heal the character
void UHealthComponent::Heal(float HealAmount)
{
	if (CurrentHealth < 100.0f)  // Assuming max health is 100
	{
		CurrentHealth += HealAmount;
		if (CurrentHealth > 100.0f)
		{
			CurrentHealth = 100.0f;  // Clamp to max health
		}
	}
}
