// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "WeaponTypes.h"
#include "EclipseRaptureCharacter.generated.h"

//Forward Declarations
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UWeaponBase;
class AItem;
class USkeletalMeshComponent;
UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
#pragma region Setup
	AEclipseRaptureCharacter();
	virtual void Tick(float DeltaTime) override;
	void HandleCrouch(float DeltaTime);
	void HandleFOV(float DeltaTime);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
#pragma endregion
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	FVector CrouchEyeOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Crouch")
	float CrouchEntranceSpeed;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Prone")
	FVector ProneEyeOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | Movement Prone")
	float ProneEntranceSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement | Movement Prone")
	float ProneEyeHeightZ;


	virtual void Jump() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon")
	void SpawnItem(TSubclassOf<AWeaponBase> WeaponToSpawn);


protected:
	virtual void BeginPlay() override;
	
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | FOV")
	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float SprintFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float AimFOV;

#pragma endregion
	
#pragma region Input Actions

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> EclipseRaptureMapping;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ProneAction;


	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LeanAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AimAction;
	
#pragma endregion
	void Move(const FInputActionValue& Value);

	/* LOOK INPUT MOVED TO BLUEPRINT
	//void Look(const FInputActionValue& Value);
	*/

	void Interact();
	void StartProne();
	void EndProne();
	void ToggleProne();
	void StartSprint();
	void EndSprint();
	void StartCrouch();
	void EndCrouch();
	void ToggleCrouch();
	void StartShooting();
	void StopShooting();
	void StartAiming();
	void StopAiming();

	UPROPERTY(BlueprintReadWrite, Category = Leaning)
	bool bResetLeaning;

	UPROPERTY(BlueprintReadWrite, Category = Aiming)
	bool IsAiming;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Character Mesh")
	TObjectPtr<USkeletalMeshComponent> PlayerBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	TObjectPtr<UCameraComponent> FirstPersonCamera;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera | Camera Sensitivity")
	float HorizontalSensitivity = 0.6f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera | Camera Sensitivity")
	float VerticalSensitivity = 0.6f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon")
	TObjectPtr<class AWeaponBase> CurrentWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon")
	EWeaponName CurrentWeaponName = EWeaponName::EWN_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons | Weapon")
	int CurrentWeaponIndex;
private:
	ECharacterMovementState CurrentMovementState = ECharacterMovementState::ECMS_Idle;

	UPROPERTY(VisibleAnywhere, Category = "Items", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AItem> CurrentOverlappingItem;
	

	UFUNCTION()
	bool CanSprint();

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

	UFUNCTION()
	void ShootTimerExpired();
	
public:	//Getters and Setters
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
};

