#pragma once

#include "CoreMinimal.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Enemies/EnemyAITypes.h"
#include "EclipseRaptureEnemy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEnd);
UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureEnemy : public AEclipseRaptureCharacter
{
    GENERATED_BODY()

public:
    AEclipseRaptureEnemy();

    virtual void Tick(float DeltaTime) override;

    // Enemy AI type (e.g., Shooter, Melee, Boss)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Properties")
    EnemyAIType AIType = EnemyAIType::EAIT_Shooter;

    // Current AI state (e.g., Idle, InCombat, InCover)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Properties")
    EEnemyAIState CurrentAIState = EEnemyAIState::EEAS_Idle; 

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

    // Check whether the enemy can fire its weapon
	UFUNCTION(BlueprintPure, Category = "Weapons")
    bool CanFire();

    // Drop items upon death
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Items")
    TArray<TSubclassOf<class AItem>> ItemsToDrop;

   

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons | Accuracy")
    float FirstShotAccuracyBonus = 20.0f;

    // Ammo management
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons")
    float MinAmmoToHold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons")
    float MaxAmmoToHold;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons")
    float AmmoCount = 30.0f;
    

#if WITH_EDITOR
    // Editor validation: Ensure designers use valid weapon setups
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
