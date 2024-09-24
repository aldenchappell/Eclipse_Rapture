// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/EclipseRaptureCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



AEclipseRaptureCharacter::AEclipseRaptureCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetupAttachment(FirstPersonCamera);
	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	GetMesh()->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}


void AEclipseRaptureCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}



void AEclipseRaptureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEclipseRaptureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Inputs
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Jump);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::DoCrouch);
		EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Prone);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Shoot);
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Melee);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Aim);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Interact);
	}
}

#pragma region Input Functions



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

void AEclipseRaptureCharacter::Jump()
{
	Super::Jump();
}

void AEclipseRaptureCharacter::DoCrouch()
{
	if (!GetCharacterMovement()->IsCrouching())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AEclipseRaptureCharacter::Prone()
{

}

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
