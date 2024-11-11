#include "Global/Components/HealthComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Character/EclipseRaptureCharacter.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    CurrentHealth = MaxHealth;
    CurrentSatiety = MaxSatiety;
    CurrentThirst = MaxThirst;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

	OwningCharacter = Cast<AEclipseRaptureCharacter>(GetOwner());

    if (OwningCharacter->CharacterType == ECharacterType::ECT_Player)
    {
        StartHealthUpdateTimer();
    }
}

#pragma region Interface Implementations

void UHealthComponent::TakeDamage_Implementation(float DamageAmount, FVector HitLocation)
{
    if (CurrentHealth > 0)
    {
		float TargetHealth = CurrentHealth - DamageAmount;
        SetCurrentHealth(FMath::Lerp(GetCurrentHealth(), TargetHealth, 1.5f));

        if (CurrentHealth <= 0)
        {
            SetCurrentHealth(0);
            OnDeathEvent.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("%s is now dead"), *GetOwner()->GetName());
        }
    }
}

void UHealthComponent::Die_Implementation()
{

}
void UHealthComponent::DropItems_Implementation(const TArray<TSubclassOf<class AItem>>& InventoryItems)
{

}

#pragma endregion

#pragma region Health

// Health Functions
float UHealthComponent::GetCurrentHealth() const
{
    return CurrentHealth;
}

void UHealthComponent::SetCurrentHealth(float Health)
{
    CurrentHealth = FMath::Clamp(Health, 0.0f, MaxHealth);
    OnHealthUpdated.Broadcast(CurrentHealth / MaxHealth);
}

void UHealthComponent::HealHealth(float HealAmount)
{
    SetCurrentHealth(CurrentHealth + HealAmount);
}
#pragma endregion

#pragma region Hunger
// Satiety (Hunger) Functions
float UHealthComponent::GetCurrentSatiety() const
{
    return CurrentSatiety;
}

void UHealthComponent::SetCurrentSatiety(float Satiety)
{
    CurrentSatiety = FMath::Clamp(Satiety, 0.0f, MaxSatiety);
    OnSatietyUpdated.Broadcast(CurrentSatiety / MaxSatiety);
}

void UHealthComponent::HealSatiety(float SatietyAmount)
{
    CurrentSatiety = FMath::Clamp(SatietyAmount, 0.0f, MaxSatiety);
    SetCurrentSatiety(CurrentSatiety + SatietyAmount);
}
#pragma endregion

#pragma region Thirst
float UHealthComponent::GetCurrentThirst() const
{
    return CurrentThirst;
}

void UHealthComponent::SetCurrentThirst(float Thirst)
{
    CurrentThirst = FMath::Clamp(Thirst, 0.0f, MaxThirst);
    OnThirstUpdated.Broadcast(CurrentThirst / MaxThirst);
}

void UHealthComponent::HealThirst(float ThirstAmount)
{
    SetCurrentThirst(CurrentThirst + ThirstAmount);
}
#pragma endregion

#pragma region Health and Thirst tick functions
//function to update the health status of the player 
void UHealthComponent::StartHealthUpdateTimer()
{
    GetWorld()->GetTimerManager().SetTimer(
        StatusUpdateTimerHandle,
        this,
        &UHealthComponent::UpdateHealthStatus,
        1.0f,//tick every second
        true
    );
}

//Update hunger, thirst, and health
void UHealthComponent::UpdateHealthStatus()
{
    //Decrease hunger and thirst over time
    float MovementHungerDepletionRate = 0.0f;
    float MovementThirstDepletionRate = 0.0f;
    if (OwningCharacter)
    {
        switch (OwningCharacter->GetCurrentMovementState())
        {
            case ECharacterMovementState::ECMS_Idle:
                MovementHungerDepletionRate = 0.05f;
                break;
			case ECharacterMovementState::ECMS_Walking:
                MovementHungerDepletionRate = WalkingHungerDepletionRate;
                break;
            case ECharacterMovementState::ECMS_Sprinting:
                MovementHungerDepletionRate = SprintingHungerDepletionRate;
                break;
        }
    }

	//Apply more hunger and thirst depletion based on the player's current movement state
	SetCurrentSatiety(MovementHungerDepletionRate > 0
                      ? CurrentSatiety - (SatietyDepletionRate + MovementHungerDepletionRate)
                      : CurrentSatiety - SatietyDepletionRate);
    
    SetCurrentThirst(MovementThirstDepletionRate > 0
                     ? CurrentThirst - (ThirstDepletionRate + MovementThirstDepletionRate)
                     : CurrentThirst - ThirstDepletionRate);
    
    //Apply damage if hunger or thirst are critically low
    ApplyHungerThirstDamage();
}

void UHealthComponent::ApplyHungerThirstDamage()
{
    bool HealthAffected = false;

    //dying of hunger and thirst
    if (CurrentThirst < ThirstDamageThreshold && CurrentSatiety < HungerDamageThreshold)
    {
        SetCurrentHealth(CurrentHealth - (HungerHealthDegenerationDamage + ThirstHealthDegenerationDamage));
        HealthAffected = true;
    }
    //dying of only hunger
    else if (CurrentSatiety <= HungerDamageThreshold) 
    {
        SetCurrentHealth(CurrentHealth - HungerHealthDegenerationDamage);
        HealthAffected = true;
    }
    //dying of only thirst
    else if (CurrentThirst <= ThirstDamageThreshold)
    {
        SetCurrentHealth(CurrentHealth - ThirstHealthDegenerationDamage);
        HealthAffected = true;
    }

    if (HealthAffected && CurrentHealth <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has died from hunger or thirst"), *GetOwner()->GetName());
    }
}

#pragma endregion