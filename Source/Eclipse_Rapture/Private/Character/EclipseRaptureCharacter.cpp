// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/EclipseRaptureCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"



AEclipseRaptureCharacter::AEclipseRaptureCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

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
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Crouch);
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

}

void AEclipseRaptureCharacter::Look(const FInputActionValue& Value)
{

}

void AEclipseRaptureCharacter::Jump()
{
	Super::Jump();
}

void AEclipseRaptureCharacter::Crouch()
{
	Super::Crouch();
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
