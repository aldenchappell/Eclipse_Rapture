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
	// Constructor
	UHealthComponent();

	// Function to override the TakeDamage event from IDamageable
	virtual void TakeDamage_Implementation(float DamageAmount, FVector HitLocation) override;

	// Health management functions
	UFUNCTION(BlueprintCallable, Category = Health)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = Health)
	void SetCurrentHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = Health)
	void Heal(float HealAmount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = Health)
	float MaxHealth = 100;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Current health value
	UPROPERTY(VisibleAnywhere, Category = Health, meta = (AllowPrivateAccess = true))
	float CurrentHealth;  // Default value
};
