// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/MeleeWeaponBase.h"
#include "CoreMinimal.h"
#include "Character/EclipseRaptureCharacter.h"
#include "PlayerMain.generated.h"


class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UCameraShakeBase;

UCLASS()
class ECLIPSE_RAPTURE_API APlayerMain : public AEclipseRaptureCharacter
{
	GENERATED_BODY()
	
public:
	APlayerMain();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Weapon Properties")
	TSubclassOf<AMeleeWeaponBase> MeleeWeaponClass;

protected:
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma region Movement Properties

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement | FOV")
	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float SprintFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement | FOV")
	float AimFOV;

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

#pragma region Camera Properties

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	FVector OriginalCameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	FVector CameraInitialOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Properties")
	float CrouchCameraHeight = -40.f; // Adjust this value based on how low you want the camera when crouched


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Sensitivity")
	float HorizontalSensitivity = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera | Camera Sensitivity")
	float VerticalSensitivity = 0.6f;

	UPROPERTY(BlueprintReadWrite, Category = Leaning)
	bool bResetLeaning;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera | Camera Properties")
	FTransform InitialCameraTransform;

#pragma endregion

#pragma region Input Actions

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> EclipseRaptureMapping;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MovementAction;

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
	void Melee();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Character | Movement | Sprinting")
	void HandleFOV(float DeltaTime);


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

#pragma region Weapon Sway

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Sway")
	float SideMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Sway")
	float MouseXSway;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Sway")
	float MouseYSway;

#pragma endregion

#pragma region Animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons | Weapon Animation")
	TObjectPtr<UAnimMontage> MeleeMontage;

#pragma endregion

#pragma region UI

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UImage> CrosshairTextureImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UTexture2D> CrosshairTexture2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UWidgetEclipseRaptureCharacter> PlayerMainUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UWidgetEclipseRaptureCharacter> BasePlayerUI;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UWidgetInventoryGrid> InventoryGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI | UI Properties")
	TObjectPtr<class UWidgetInventoryWheel> QuickAccessWheel;

	

	

#pragma endregion

#pragma region Flashlight

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character | Components")
	TObjectPtr<class UFlashlightComponent> FlashlightComponent;
#pragma endregion

#pragma region Weapon Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TObjectPtr<AWeaponBase> MeleeWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	bool bCanMelee = true;

#pragma endregion
private:

	UFUNCTION(Blueprintcallable, Category = "Character | Movement", meta = (AllowPrivateAccess = "true"))
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

public:

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
	AWeaponBase* GetMeleeWeapon() const { return MeleeWeapon; }

	UFUNCTION(Blueprintcallable)
	bool SetCanMelee(bool CanMelee) { return bCanMelee = CanMelee; }

	UFUNCTION(Blueprintcallable)
	class UInputMappingContext* GetCharacterMappingContext() const { return EclipseRaptureMapping; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Blueprintcallable, Category = "Building")
	UBuildingComponent* GetBuildingComponent() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Blueprintcallable, Category = "Building")
	UStaticMeshComponent* GetBuildingBlueprintStaticMesh() const;

	UFUNCTION(Blueprintcallable, Category = "UI | UI Properties")
	void SetCrosshairTexture(UTexture2D* Texture);
};
