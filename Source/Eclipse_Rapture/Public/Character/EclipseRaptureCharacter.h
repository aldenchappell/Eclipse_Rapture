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
class UCameraShakeBase;

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

#pragma endregion
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon | Weapon Properties")
	void SpawnItem(TSubclassOf<AWeaponBase> WeaponToSpawn);

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Weapon Properties")
	TSubclassOf<AWeaponBase> MeleeWeaponClass;

	//For ui mostly
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	int32 CurrentWeaponAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Aiming")
	FVector PlayerADSOffset;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | Movement Mantle")
	bool bCanMantle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Aiming")
	float ADSSpeed = .35f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Aiming")
	FTransform DefaultTorsoTransform;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float MantleTraceDistance = 100.f;

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

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> UnarmedAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> PrimaryAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> SecondaryAction;
	
#pragma endregion

#pragma region Input Functions
	void Interact();
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UImage> CrosshairTextureImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UTexture2D> CrosshairTexture2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UUserWidget> PlayerMainUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UWidgetEclipseRaptureCharacter> BasePlayerUI;

	UFUNCTION(Blueprintcallable, Category = "UI | UI Properties")
	void SetCrosshairTexture(UTexture2D* Texture);



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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TObjectPtr<AWeaponBase> MeleeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	bool bCanMelee = true;

	UFUNCTION(BlueprintCallable, Category = "Weapon | Weapon Logic")
	void OnWeaponUpdateSetAmmo();
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | Camera Properties")
	FTransform InitialCameraTransform;

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
	
#pragma region Headbobbing

	UPROPERTY()
	bool bEnableHeadbobbing = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Movement | Headbobbing")
	TSubclassOf<UCameraShakeBase> IdleShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Movement | Headbobbing")
	TSubclassOf<UCameraShakeBase> WalkShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Movement | Headbobbing")
	TSubclassOf<UCameraShakeBase> SprintShake;

	UFUNCTION()
	void HandleHeadbob();

#pragma endregion

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
	UPROPERTY(VisibleAnywhere, Category = "Weapon | Shooting | Shooting Properties")
	FTimerHandle ShootTimer;
#pragma region Swapping Weapons
	UFUNCTION()
	void SwapWeapon(EWeaponClass NewWeaponClass);

	UFUNCTION()
	void EquipWeapon(AWeaponBase* Weapon);

	UFUNCTION()
	AWeaponBase* GetCurrentWeaponByClass(EWeaponClass WeaponClass);

	//for weapon swapping
	UPROPERTY()
	TObjectPtr<AWeaponBase> CurrentWeapon;


	FORCEINLINE void EquipUnarmed();
	FORCEINLINE void EquipPrimaryWeapon();
	void SetSwapTimer();
	FORCEINLINE void EquipSecondaryWeapon();

	// Timer handle to manage swap cooldown
	FTimerHandle WeaponSwapTimerHandle;

	// Flag to track if swapping is allowed
	bool bCanSwapWeapon = true;

	// Helper function to reset the swap ability
	void ResetSwap();
	
#pragma endregion

#pragma region Getters And Setters

public:	

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

	UFUNCTION(Blueprintcallable, meta = (BlueprintThreadSafe))
	bool SetCanMove(bool NewCanMove) { return bCanMove = NewCanMove; }

	UFUNCTION(Blueprintcallable)
	AWeaponBase* GetMeleeWeapon() const { return MeleeWeapon; }

	UFUNCTION(Blueprintcallable)
	bool SetCanMelee(bool CanMelee) { return bCanMelee = CanMelee; }

	UFUNCTION(Blueprintcallable)
	bool GetIsReloading() const { return bIsReloading; }

	UFUNCTION(Blueprintcallable)
	void SetIsReloading(bool Reloading) { bIsReloading = Reloading; }

#pragma endregion
};