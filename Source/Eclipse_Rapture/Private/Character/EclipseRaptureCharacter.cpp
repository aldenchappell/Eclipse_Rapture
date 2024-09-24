// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/EclipseRaptureCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterTypes.generated.h"



AEclipseRaptureCharacter::AEclipseRaptureCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Setup collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//Setup movement speeds
	WalkMovementSpeed = 450.f;
	SprintMovementSpeed = 600.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.f;
	ProneMovementSpeed = 100.f;
	GetCharacterMovement()->MaxWalkSpeed = WalkMovementSpeed;

	//Setup camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCamera->bUsePawnControlRotation = true;
	DefaultFOV = FirstPersonCamera->FieldOfView;
	SprintFOV = DefaultFOV * 1.1f;

	//Setup mesh
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(FirstPersonCamera);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	GetMesh()->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	//Setup crouching
	CrouchEyeOffset = FVector(0.f);
	CrouchEntranceSpeed = 12.f;


}


void AEclipseRaptureCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}


void AEclipseRaptureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region Handle Crouching
	float CrouchInterpTime = FMath::Min(1.f, CrouchEntranceSpeed * DeltaTime);
	CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
#pragma endregion

}

void AEclipseRaptureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Inputs
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Look);

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::StopJumping);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::EndCrouch);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::EndSprint);

		//Proning
		EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::StartProne);
		EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::EndProne);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Shoot);
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Melee);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Aim);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Interact);
	}
}

void AEclipseRaptureCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.f) return;

	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
}

void AEclipseRaptureCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.f) return;

	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
}

void AEclipseRaptureCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	if (FirstPersonCamera)
	{
		FirstPersonCamera->GetCameraView(DeltaTime, OutResult);
		OutResult.Location += CrouchEyeOffset;
	}
}

#pragma region Input Functions





void AEclipseRaptureCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

#pragma region Movement
void AEclipseRaptureCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AEclipseRaptureCharacter::Jump()
{
	Super::Jump();
}

void AEclipseRaptureCharacter::StartCrouch()
{
	Crouch();
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeedCrouched;
}

void AEclipseRaptureCharacter::EndCrouch()
{
	UnCrouch();
	GetCharacterMovement()->MaxWalkSpeed = WalkMovementSpeed;
}

void AEclipseRaptureCharacter::StartProne()
{

}

void AEclipseRaptureCharacter::EndProne()
{

}

void AEclipseRaptureCharacter::StartSprint()
{
	if (!CanSprint()) return;

	CurrentMovementState = ECharacterMovementState::ECMS_Sprinting;

	GetCharacterMovement()->MaxWalkSpeed = SprintMovementSpeed;
	FirstPersonCamera->FieldOfView = SprintFOV;

}

void AEclipseRaptureCharacter::EndSprint()
{
	CurrentMovementState = ECharacterMovementState::ECMS_Walking;

	GetCharacterMovement()->MaxWalkSpeed = WalkMovementSpeed;

	FirstPersonCamera->FieldOfView = DefaultFOV;
}


bool AEclipseRaptureCharacter::CanSprint()
{
	// Ensure the character is moving and not in a crouching or prone state
	return CurrentMovementState != ECharacterMovementState::ECMS_Crouching &&
		CurrentMovementState != ECharacterMovementState::ECMS_Prone &&
		GetVelocity().Size() > 0;  // Ensure the character is moving
}

#pragma endregion




void AEclipseRaptureCharacter::Interact()
{

}

void AEclipseRaptureCharacter::Shoot()
{

}

void AEclipseRaptureCharacter::Melee()
{

}

void AEclipseRaptureCharacter::Aim()
{

}



#pragma endregion
