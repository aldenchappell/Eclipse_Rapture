// HealthComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Damageable.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UHealthComponent : public UActorComponent, public IDamageable
{
	GENERATED_BODY()

public:
	UHealthComponent();

	virtual void TakeDamage_Implementation(float DamageAmount, FVector HitLocation) override;

#pragma region Health
	UFUNCTION(BlueprintCallable, Category = Health)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetCurrentHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = Health)
	void Heal(float HealAmount);


	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = Health)
	float MaxHealth = 100;

#pragma endregion

#pragma region Satiety
	UFUNCTION(BlueprintCallable, Category = Food)
	void HealSatiety(float SatietyAmount);

	UFUNCTION(BlueprintCallable, Category = Food, meta = (ClampMin = 0.0))
	float GetCurrentSatiety() const;

	UFUNCTION(BlueprintCallable, Category = Food)
	void SetCurrentSatiety(float Satiety);

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = Health)
	float MaxSatiety = 100;

#pragma endregion

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, Category = Health, meta = (AllowPrivateAccess = true))
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = Food, meta = (AllowPrivateAccess = true))
	float CurrentSatiety;
};
