#pragma once

#include "CoreMinimal.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Enemies/EnemyAITypes.h"
#include "EclipseRaptureEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnequipWeapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);
UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureEnemy : public AEclipseRaptureCharacter
{
    GENERATED_BODY()

public:
    AEclipseRaptureEnemy();

    virtual void Tick(float DeltaTime) override;

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Weapons | Delegates")
    FOnEquipWeapon OnEquipWeapon;

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Weapons | Delegates")
    FOnUnequipWeapon OnUnequipWeapon;

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Weapons | Delegates")
    FOnAttack OnAttack;

    UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Weapons | Delegates")
    FOnAttackEnd OnAttackEnd;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI | AI Properties")
    class UBehaviorTree* BehaviorTree;

#pragma region Animation

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Animation")
    TObjectPtr<class UAnimMontage> EquipPrimaryMontage;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Animation")
    TObjectPtr<class UAnimMontage> EquipSecondaryMontage;

#pragma endregion

    // List of weapon classes to spawn and assign to `CurrentWeapons`
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    TMap<EWeaponClass, TSubclassOf<AWeaponBase>> StartingWeapons;

    //What weapon class should the enemy start the game with?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
    EWeaponClass PreferredStartingWeaponClass = EWeaponClass::EWC_Primary;

    // Equip the starting weapon based on the enemy's setup
    void EquipStartingWeapon();

    // Ensure the enemy's weapon configuration is valid
    UFUNCTION(BlueprintCallable, Category = "Weapons | Validation")
    bool IsValidWeaponConfiguration() const;

    // Add a weapon to the enemy from a `WeaponBase` class
    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void AddWeapon(TSubclassOf<class AWeaponBase> WeaponClass, EWeaponClass WeaponSlot);

    // Spawns and equips weapons based on `StartingWeapons`
	UFUNCTION(BlueprintCallable, Category = "Weapons")
    void SpawnStartingWeapons();

#if WITH_EDITOR
    // Editor validation: Ensure designers use valid weapon setups
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
