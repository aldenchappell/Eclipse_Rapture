// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "WeaponTypes.h"
#include "Interfaces/CharacterData.h"
#include "Interfaces/Damageable.h"
#include "EclipseRaptureCharacter.generated.h"

//Forward Declarations
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class AWeaponBase;
class AItem;
class USkeletalMeshComponent;
class UCameraShakeBase;

UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureCharacter :
	public ACharacter, public ICharacterData, public IDamageable
{
	GENERATED_BODY()

	

public:
#pragma region Setup
	AEclipseRaptureCharacter();
	virtual void Tick(float DeltaTime) override;
	//void HandleFootsteps();
	void HandleCrouch(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Character Properties")
	ECharacterType CharacterType;
#pragma endregion

	//For ui mostly
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	int32 CurrentWeaponAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Aiming")
	FVector PlayerADSOffset;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon | Weapon Properties")
	void SpawnItem(TSubclassOf<AWeaponBase> WeaponToSpawn);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Character Mesh")
	TObjectPtr<USkeletalMeshComponent> PlayerBodyMesh;

#pragma region Components

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Components | Health Component")
	TObjectPtr<class UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory | Components")
	TObjectPtr<class UInventoryComponent> InventoryComponent;

#pragma endregion
	
#pragma region Damageable Implementations
	virtual void TakeDamage_Implementation(float DamageAmount, FVector HitLocation) override;

	virtual void Die_Implementation() override;

	virtual void DropItems_Implementation(const TArray<TSubclassOf<class AItem>>& InventoryItems) override;

	virtual float GetMaxHealth_Implementation() override;
	virtual float GetCurrentHealth_Implementation() override;
	virtual float GetCriticalHealthThreshold_Implementation() override;
#pragma endregion

protected:
	virtual void BeginPlay() override;

#pragma region Weapon Swapping

	UFUNCTION(BlueprintCallable)
	void SwapWeapon(EWeaponClass NewWeaponClass);

	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetCurrentWeaponByClass(EWeaponClass WeaponClass);

	//for weapon swapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TObjectPtr<AWeaponBase> CurrentWeapon;

	UFUNCTION(BlueprintCallable, Category = "Weapon | Weapon Properties")
	void OnWeaponUpdateSetAmmo();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon | Weapon Properties")
	void EquipWeapon(AWeaponBase* Weapon);

	UFUNCTION(Blueprintcallable)
	virtual void EquipUnarmed();

	UFUNCTION(Blueprintcallable)
	virtual void EquipPrimaryWeapon();
	
	UFUNCTION(Blueprintcallable)
	virtual void EquipSecondaryWeapon();

	void SetSwapTimer();

	// Timer handle to manage swap cooldown
	FTimerHandle WeaponSwapTimerHandle;

	// Flag to track if swapping is allowed
	bool bCanSwapWeapon = true;

	// Helper function to reset the swap ability
	void ResetSwap();
#pragma endregion


	UPROPERTY(VisibleAnywhere, Category = "Items")
	TObjectPtr<AItem> CurrentOverlappingItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character | Character Movement")
	ECharacterMovementState CurrentMovementState = ECharacterMovementState::ECMS_Idle;

#pragma region Movement Values

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	FVector CrouchEyeOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	float CrouchEntranceSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	bool bCanCrouch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	bool bIsCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	bool ToggleCrouching = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	float CameraCrouchOffset = -40.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Prone")
	FVector ProneEyeOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Prone")
	float ProneEntranceSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Movement Prone")
	float ProneEyeHeightZ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	bool bIsProning;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | Movement Mantle")
	bool bCanMantle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Aiming")
	float ADSSpeed = .35f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Aiming")
	FTransform DefaultTorsoTransform;

#pragma endregion

#pragma region Movement Properties

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement | Movement Properties")
	float StoredWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement | Movement Properties")
	float StoredSprintSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement | Movement Properties")
	float WalkMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement | Movement Properties")
	float SprintMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Properties")
	float ProneMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Properties")
	float AimMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float MantleTraceDistance = 100.f;

#pragma endregion
	





#pragma region Weapon Properties

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	int32 PrimaryAmmo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	int32 SecondaryAmmo;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon | Weapon Logic")
	bool bIsAiming;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon | Weapon Logic")
	bool bIsReloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Logic")
	bool bHasPrimaryWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Logic")
	bool bHasSecondaryWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Weapon Logic")
	float WeaponSwapCooldown = 2.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TMap<EWeaponClass, TObjectPtr<AWeaponBase>> CurrentWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TObjectPtr<AWeaponBase> CurrentWeaponBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	EWeaponClass CurrentWeaponClass = EWeaponClass::EWC_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	EWeaponType CurrentWeaponType = EWeaponType::EWT_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	EWeaponName CurrentWeaponName = EWeaponName::EWN_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	int CurrentWeaponIndex;

#pragma region Accuracy

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons | Accuracy")
	float Accuracy = 80.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Character | Weapons | Accuracy", meta = (ClampMin = "5", ClampMax = "50"))
	float MaxAccuracy = 5.f;


#pragma endregion
#pragma endregion

#pragma region Mantling

	UFUNCTION(BlueprintCallable, Category = "Movement | Mantle")
	void DoMantleTrace(float TraceLength, float TraceZOffset, float FallHeightAdjust, FVector& MantlePos1, FVector& MantlePos2);

	UFUNCTION(BlueprintImplementableEvent, Category = "Movement | Mantle")
	void Mantle();

	UPROPERTY(BlueprintReadWrite, Category = "Movement | Mantle")
	FVector MantlePositionOne;

	UPROPERTY(BlueprintReadWrite, Category = "Movement | Mantle")
	FVector MantlePositionTwo;




#pragma endregion
	


#pragma region Clothing

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character | Clothing")
	TObjectPtr<USkeletalMeshComponent> PlayerHelmetMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character | Clothing")
	TObjectPtr<USkeletalMeshComponent> PlayerChestMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character | Clothing")
	TObjectPtr<USkeletalMeshComponent> PlayerPantsMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character | Clothing")
	TObjectPtr<USkeletalMeshComponent> PlayerShoesMesh;

#pragma endregion

	

private:
	bool bCanMove = true;


#pragma region Getters And Setters

public:	

	UFUNCTION(BlueprintCallable, Category = "Character | Movement")
	ECharacterMovementState GetCurrentMovementState() const { return CurrentMovementState; }

	UFUNCTION(Blueprintcallable, meta = (BlueprintThreadSafe))
	bool GetCanMove() const { return bCanMove; }

	UFUNCTION(Blueprintcallable, meta = (BlueprintThreadSafe))
	bool SetCanMove(bool NewCanMove) { return bCanMove = NewCanMove; }

	UFUNCTION(Blueprintcallable)
	bool GetIsReloading() const { return bIsReloading; }

	UFUNCTION(Blueprintcallable)
	void SetIsReloading(bool Reloading) { bIsReloading = Reloading; }

	UFUNCTION(Blueprintcallable)
	class UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION(Blueprintcallable)
	class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UFUNCTION(Blueprintcallable)
	AItem* SetCurrentlyOverlappingItem(AItem* Item) { return CurrentOverlappingItem = Item; }

	UFUNCTION(Blueprintcallable)
	AItem* GetCurrentlyOverlappingItem() const { return CurrentOverlappingItem; }

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character | Weapons")
	void GetWeaponOfType(EWeaponClass WeaponType, AWeaponBase*& Weapon, bool& HasWeaponOfType);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character | Weapons")
	AWeaponBase* GetCurrentWeapon();

	//Adjust aim direction based on accuracy
	UFUNCTION(BlueprintCallable, Category = "Character | Weapons | Accuracy")
	FVector GetAdjustedAimDirection(const FVector& OriginalDirection) const;
#pragma endregion
};
