#include "Global/Components/HealthComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AI/AISystemBase.h"

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
    UE_LOG(LogTemp, Warning, TEXT("Attack tokens remaining: %d"), AttackTokensCount);
}

#pragma region Health



void UHealthComponent::SetCurrentHealth(float Health)
{
    CurrentHealth = FMath::Clamp(Health, 0.0f, MaxHealth);
    OnHealthUpdated.Broadcast(CurrentHealth / MaxHealth);
}

void UHealthComponent::HealHealth(float HealAmount)
{
    SetCurrentHealth(CurrentHealth + HealAmount);
	OnHealthUpdated.Broadcast(CurrentHealth / MaxHealth);
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
	OnSatietyUpdated.Broadcast(CurrentSatiety / MaxSatiety);
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
    OnThirstUpdated.Broadcast(CurrentThirst / MaxThirst);
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

#pragma region Attack Tokens - Implemented here and called in enemy and player blueprints.

void UHealthComponent::ReserveAttackToken(int32 TokenAmount, bool& Success)
{
	if (AttackTokensCount >= TokenAmount)
	{
		AttackTokensCount -= TokenAmount;
		Success = true;
		UE_LOG(LogTemp, Warning, TEXT("Attack Token Reserved, tokens remaining: %d"), AttackTokensCount);
	}
	else
	{
		Success = false;
        UE_LOG(LogTemp, Warning, TEXT("Failed to reserve Attack Token, tokens remaining: % d"), AttackTokensCount);
	}
}

void UHealthComponent::ReturnAttackToken(int32 TokenAmount)
{
	AttackTokensCount += TokenAmount;
}
