#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Damageable.h"
#include "HealthComponent.generated.h"

// Blueprint multicast delegates to notify UI updates
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

    // Delegates to broadcast changes to UI
    UPROPERTY(BlueprintAssignable, Category = "Health | Delegates")
    FOnHealthUpdated OnHealthUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Satiety | Delegates")
    FOnSatietyUpdated OnSatietyUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Thirst | Delegates")
    FOnThirstUpdated OnThirstUpdated;

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

protected:
    virtual void BeginPlay() override;

private:
    float CurrentHealth;
    float CurrentSatiety;
    float CurrentThirst;
};
