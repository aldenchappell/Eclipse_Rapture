// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "WeaponTypes.h"
#include "Interfaces/CharacterData.h"
#include "EclipseRaptureCharacter.generated.h"

//Forward Declarations
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UWeaponBase;
class AItem;
class USkeletalMeshComponent;

UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureCharacter : public ACharacter, public ICharacterData
{
	GENERATED_BODY()

public:
#pragma region Setup
	AEclipseRaptureCharacter();
	virtual void Tick(float DeltaTime) override;
	//void HandleFootsteps();
	void HandleCrouch(float DeltaTime);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

#pragma endregion
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon | Weapon Properties")
	void SpawnItem(TSubclassOf<AWeaponBase> WeaponToSpawn);

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Weapon Properties")
	TSubclassOf<AWeaponBase> MeleeWeaponClass;

	//For ui mostly
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	int32 CurrentWeaponAmmo;

protected:
	virtual void BeginPlay() override;
#pragma region Movement Values
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Character Mesh")
	TObjectPtr<USkeletalMeshComponent> PlayerBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character | Character Movement")
	ECharacterMovementState CurrentMovementState = ECharacterMovementState::ECMS_Idle;

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

#pragma endregion

#pragma region Movement Properties
	void Move(const FInputActionValue& Value);

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | FOV")
	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float SprintFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float AimFOV;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadonly, Category = "Character | Footsteps")
	TObjectPtr<class UFootstepComponent> FootstepComponent;

#pragma endregion
	
#pragma region Input Actions

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> EclipseRaptureMapping;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MeleeAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ReloadAction;

	
#pragma endregion

#pragma region Input Functions
	void Interact();
	void StartAiming();
	void StopAiming();
	void Melee();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character | Movement | Sprinting")
	void HandleFOV(float DeltaTime);

	
#pragma endregion

#pragma region Sprinting
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character | Movement | Sprinting")
	float CurrentStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Movement | Sprinting")
	float MaxStamina = 15.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Movement | Sprinting")
	float StaminaIncreaseRate = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character | Movement | Sprinting")
	float StaminaDecreaseRate = 5.f;


	UPROPERTY(BlueprintReadWrite, Category = "Character | Movement | Sprinting")
	FTimerHandle SprintTimer;

#pragma endregion

#pragma region UI


#pragma endregion

#pragma region Weapon Properties

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	int32 PrimaryAmmo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	int32 SecondaryAmmo;

	UPROPERTY(BlueprintReadWrite, Category = Aiming)
	bool IsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon Logic")
	bool bHasPrimaryWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon Logic")
	bool bHasSecondaryWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	TMap<EWeaponClass, TObjectPtr<AWeaponBase>> CurrentWeapons;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	EWeaponClass CurrentWeaponClass = EWeaponClass::EWC_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	EWeaponType CurrentWeaponType = EWeaponType::EWT_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	EWeaponName CurrentWeaponName = EWeaponName::EWN_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	int CurrentWeaponIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	TObjectPtr<AWeaponBase> MeleeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon Properties")
	bool bCanMelee = true;
#pragma endregion

#pragma region Camera Properties

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	FVector OriginalCameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	FVector CameraInitialOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	float CrouchCameraHeight = -40.f; // Adjust this value based on how low you want the camera when crouched


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera | Camera Sensitivity")
	float HorizontalSensitivity = 0.6f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera | Camera Sensitivity")
	float VerticalSensitivity = 0.6f;

	UPROPERTY(BlueprintReadWrite, Category = Leaning)
	bool bResetLeaning;

#pragma endregion
	
#pragma region Animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Animation")
	TObjectPtr<UAnimMontage> MeleeMontage;

#pragma endregion

#pragma region Weapon Sway

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Sway")
	float SideMove;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Sway")
	float MouseXSway;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Sway")
	float MouseYSway;

#pragma endregion
	
	UFUNCTION(BlueprintCallable, Category = "Weapon | Weapon Logic")
	void OnWeaponUpdateSetAmmo();
private:
	

	UPROPERTY(VisibleAnywhere, Category = "Items", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AItem> CurrentOverlappingItem;
	
	UFUNCTION(Blueprintcallable, Category = "Character | Movement", meta = (AllowPrivateAccess = "true"))
	bool CanSprint();

	bool bCanMove = true;

	float SprintFOVMultiplier = 1.2f;
	float AimFOVMultiplier = .6f;

	//Sensitivity and Input values
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float InputPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float InputYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float InputRoll;

	bool bEnableSensitivityChanges = false;
	
	//Shooting Properties
	UPROPERTY(VisibleAnywhere, Category = "Shooting | Shooting Properties")
	FTimerHandle ShootTimer;

	//UFUNCTION()
	//void ShootTimerExpired();
	
public:	//Getters and Setters

	UFUNCTION(BlueprintCallable, Category = "Character | Movement")
	ECharacterMovementState GetCurrentMovementState() const { return CurrentMovementState; }

	UFUNCTION(Blueprintcallable)
	float GetSprintFOVMultiplier() const { return SprintFOVMultiplier; }
	
	UFUNCTION(Blueprintcallable)
	float GetHorizontalSensitivity() const { return HorizontalSensitivity; }

	UFUNCTION(Blueprintcallable)
	float GetVerticalSensitivity() const { return VerticalSensitivity; }


	UFUNCTION(Blueprintcallable)
	float SetHorizontalSensitivity(float Sensitivity) { return HorizontalSensitivity = Sensitivity; }

	UFUNCTION(Blueprintcallable)
	float SetVerticalSensitivity(float Sensitivity) { return VerticalSensitivity = Sensitivity; }

	UFUNCTION(Blueprintcallable)
	AItem* SetCurrentlyOverlappingItem(AItem* Item) { return CurrentOverlappingItem = Item; }

	UFUNCTION(Blueprintcallable, meta = (BlueprintThreadSafe))
	bool GetCanMove() const { return bCanMove; }

	UFUNCTION(Blueprintcallable)
	AWeaponBase* GetMeleeWeapon() const { return MeleeWeapon; }

	UFUNCTION(Blueprintcallable)
	bool SetCanMelee(bool CanMelee) { return bCanMelee = CanMelee; }
};