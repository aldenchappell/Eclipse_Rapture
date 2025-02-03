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

    

    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Item Properties | Data")
    TObjectPtr<class UEnemyDataComponent> EnemyData;

    // Equip the starting weapon based on the enemy's setup
    void EquipStartingWeapon();

    // Add a weapon to the enemy from a `WeaponBase` class
    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void AddWeapon(TSubclassOf<class AWeaponBase> WeaponClass, EWeaponClass WeaponSlot);

    // Spawns and equips weapons based on `StartingWeapons`
	UFUNCTION(BlueprintCallable, Category = "Weapons")
    void SpawnStartingWeapons();


public:

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "Data | Enemy Data")
    FORCEINLINE FDataTableRowHandle GetEnemyID();

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "Data | Enemy Data")
    FORCEINLINE FEnemyData GetEnemyData();
};
