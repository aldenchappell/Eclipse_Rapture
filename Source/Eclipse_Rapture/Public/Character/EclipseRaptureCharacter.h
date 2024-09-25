// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "EclipseRaptureCharacter.generated.h"

//Forward Declarations
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
#pragma region Setup
	AEclipseRaptureCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Crouch)
	FVector CrouchEyeOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Crouch)
	float CrouchEntranceSpeed;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Prone)
	FVector ProneEyeOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Prone)
	float ProneEntranceSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Prone)
	float ProneEyeHeightZ;

#pragma endregion
	virtual void Jump() override;
	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float StoredWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float StoredSprintSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float WalkMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float SprintMovementSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float ProneMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = FOV)
	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FOV)
	float SprintFOV;

	
#pragma region Input Actions

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* EclipseRaptureMapping;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ProneAction;


	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SprintAction;
	
#pragma endregion
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


	void Interact();
	void StartProne();
	void EndProne();
	void ToggleProne();
	void StartSprint();
	void EndSprint();
	void StartCrouch();
	void EndCrouch();
	void ToggleCrouch();

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FirstPersonCamera;

private:
	ECharacterMovementState CurrentMovementState = ECharacterMovementState::ECMS_Idle;

	bool ShouldSprint;

	UFUNCTION()
	bool CanSprint();
	//Getters and Setters
public:	

	
	

};
