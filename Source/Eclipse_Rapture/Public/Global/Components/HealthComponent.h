#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Damageable.h"
#include "HealthComponent.generated.h"


// Blueprint multicast delegates to notify UI updates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdated, float, HealthPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatietyUpdated, float, SatietyPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThirstUpdated, float, ThirstPercent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UHealthComponent : public UActorComponent, public IDamageable
{
    GENERATED_BODY()

public:
    UHealthComponent();

    virtual void TakeDamage_Implementation(float DamageAmount, FVector HitLocation) override;

	virtual void Die_Implementation() override;

    virtual void DropItems_Implementation(const TArray<TSubclassOf<class AItem>>& InventoryItems) override;

    // Health functions
    UFUNCTION(BlueprintCallable, Category = Health)
    float GetCurrentHealth() const;

    UFUNCTION(BlueprintCallable, Category = Health)
    void SetCurrentHealth(float Health);

    UFUNCTION(BlueprintCallable, Category = Health)
    void HealHealth(float HealAmount);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health)
    float MaxHealth = 100.0f;

    // Satiety (Hunger) functions
    UFUNCTION(BlueprintCallable, Category = Satiety)
    float GetCurrentSatiety() const;

    UFUNCTION(BlueprintCallable, Category = Satiety)
    void SetCurrentSatiety(float Satiety);

    UFUNCTION(BlueprintCallable, Category = Satiety)
    void HealSatiety(float SatietyAmount);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Satiety)
    float MaxSatiety = 100.0f;

    // Thirst functions
    UFUNCTION(BlueprintCallable, Category = Thirst)
    float GetCurrentThirst() const;

    UFUNCTION(BlueprintCallable, Category = Thirst)
    void SetCurrentThirst(float Thirst);

    UFUNCTION(BlueprintCallable, Category = Thirst)
    void HealThirst(float ThirstAmount);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Thirst)
    float MaxThirst = 100.0f;

    // Delegates to update UI
    UPROPERTY(BlueprintAssignable, Category = "Health | Delegates")
    FOnHealthUpdated OnHealthUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Satiety | Delegates")
    FOnSatietyUpdated OnSatietyUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Thirst | Delegates")
    FOnThirstUpdated OnThirstUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Health | Delegates")
    FOnDeath OnDeathEvent;

protected:
    virtual void BeginPlay() override;

    void StartHealthUpdateTimer();

    //when does the player start taking damage from hunger?
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health | Damage")
    float HungerDamageThreshold = 10.0f;

    //when does the player start taking damage from thirst?
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health | Damage")
    float ThirstDamageThreshold = 10.0f;

    //how much damage the player takes per tick from hunger once depleted
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Satiety | Depletion")
    float SatietyDepletionRate = 0.05f;

    //how much damage the player takes per tick from hunger once depleted
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thirst | Depletion")
    float ThirstDepletionRate = 0.075f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health | Damage")
    float HungerHealthDegenerationDamage = 0.02f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health | Damage")
    float ThirstHealthDegenerationDamage = 0.03f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health | Damage")
    float IdleHungerDepletionRate = 0.05f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health | Damage")
	float WalkingHungerDepletionRate = 0.075f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health | Damage")
    float SprintingHungerDepletionRate = 0.075f;

private:
    float CurrentHealth;
    float CurrentSatiety;
    float CurrentThirst;

    // Timer for periodic status updates
    FTimerHandle StatusUpdateTimerHandle;

    // Helper functions for status management
    void UpdateHealthStatus();
    void ApplyHungerThirstDamage();

    class AEclipseRaptureCharacter* OwningCharacter;
};