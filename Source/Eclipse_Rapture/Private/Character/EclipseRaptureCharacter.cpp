

#include "Character/EclipseRaptureCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterTypes.generated.h"
#include "Items/Item.h"
#include "Weapons/WeaponBase.h"
#include "Global/Components/FootstepComponent.h"

AEclipseRaptureCharacter::AEclipseRaptureCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    //Setup collision capsule
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    //Setup movement speeds
    WalkMovementSpeed = 450.f;
    StoredWalkSpeed = WalkMovementSpeed;
    SprintMovementSpeed = StoredWalkSpeed * 1.5f;
    StoredSprintSpeed = SprintMovementSpeed;
    GetCharacterMovement()->MaxWalkSpeedCrouched = 150.f;
    ProneMovementSpeed = 100.f;
    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;

    //Setup player mesh
    GetMesh()->SetOnlyOwnerSee(true);
    GetMesh()->SetupAttachment(GetRootComponent());
    GetMesh()->bCastDynamicShadow = false;
    GetMesh()->CastShadow = false;
    GetMesh()->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    //Setup crouching
    CrouchEyeOffset = FVector(0.f);
    CrouchEntranceSpeed = 12.f;

    //Setup proning
    ProneEyeOffset = FVector(0.f);
    ProneEntranceSpeed = 2.f;
    ProneEyeHeightZ = -50.f;

    //fov
    AimFOV = DefaultFOV * AimFOVMultiplier;

    //Add footstep actor component
	//FootstepComponent = CreateDefaultSubobject<UFootstepComponent>(TEXT("FootstepComponent"));
}

void AEclipseRaptureCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;
}


void AEclipseRaptureCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleFOV(DeltaTime);
    HandleFootsteps();

}
void AEclipseRaptureCharacter::HandleFootsteps()
{
    if (FootstepComponent)
    {
        FootstepComponent->DetermineFootstepOffset(CurrentMovementState);
        FootstepComponent->FootstepTrace(this);
    }
}
void AEclipseRaptureCharacter::HandleCrouch(float DeltaTime)
{
    //Handle crouching interpolation
    float CrouchInterpTime = FMath::Min(1.f, CrouchEntranceSpeed * DeltaTime);
    CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
}
void AEclipseRaptureCharacter::HandleFOV(float DeltaTime)
{
    //Determine the target FOV based on the current movement state
    /*float TargetFOV = (CurrentMovementState == ECharacterMovementState::ECMS_Sprinting) ? SprintFOV : DefaultFOV;*/

    float TargetFOV = DefaultFOV;
    if (CurrentMovementState == ECharacterMovementState::ECMS_Aiming)
    {
        TargetFOV = AimFOV;
    }
	else if (CurrentMovementState == ECharacterMovementState::ECMS_Sprinting && GetVelocity().Size() > 0)
	{
		TargetFOV = SprintFOV;
	}
    else
    {
        TargetFOV = DefaultFOV;
    }

    //Lerp the FOV between current and target FOV
    FirstPersonCamera->FieldOfView = FMath::FInterpTo(FirstPersonCamera->FieldOfView, TargetFOV, DeltaTime, 5.0f); // 5.0f is the interpolation speed
}
#pragma region Setup Input
void AEclipseRaptureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Bind Inputs
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        //Movement
        EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Move);

        //Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::StopJumping);

        //Sprinting
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::StartSprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::EndSprint);

        //Proning (Toggled)
        //EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::ToggleProne);

        //Interact
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Interact);

        //Shoot
        //EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::StartShooting);
        //EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::StopShooting);

        //Aim
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::StartAiming);
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::StopAiming);
    }
}
#pragma endregion
void AEclipseRaptureCharacter::Interact()
{
    if (CurrentOverlappingItem && CurrentOverlappingItem->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
    {
        // Call the Execute_Interact function for the interface
        IInteractInterface::Execute_Interact(CurrentOverlappingItem, this);
		CurrentOverlappingItem = nullptr;
    }
}

void AEclipseRaptureCharacter::StartAiming()
{
    AWeaponBase* Weapon = CurrentWeapons.FindRef(CurrentWeaponClass);
    if (Weapon)
    {
        CurrentMovementState = ECharacterMovementState::ECMS_Aiming;
        GetCharacterMovement()->MaxWalkSpeed = AimMovementSpeed;
        IsAiming = true;

        UE_LOG(LogTemp, Warning, TEXT("Started aiming with weapon class: %s"), *UEnum::GetValueAsString(CurrentWeaponClass));
    }
}



void AEclipseRaptureCharacter::StopAiming()
{
    AWeaponBase* Weapon = CurrentWeapons.FindRef(CurrentWeaponClass);
    if (Weapon)
    {
        CurrentMovementState = ECharacterMovementState::ECMS_Walking;
        GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;
        IsAiming = false;

        UE_LOG(LogTemp, Warning, TEXT("Stopped aiming with weapon class: %s"), *UEnum::GetValueAsString(CurrentWeaponClass));
    }
}





#pragma endregion

void AEclipseRaptureCharacter::SpawnItem_Implementation(TSubclassOf<AWeaponBase> WeaponToSpawn)
{
}


#pragma region Movement


#pragma region Deprecated Look Input
/* LOOK INPUT MOVED TO BLUEPRINT
* //void AEclipseRaptureCharacter::Look(const FInputActionValue& Value)
//{
//    FVector2D LookAxisVector = Value.Get<FVector2D>();
//
//    if (Controller != nullptr)
//    {  
//        float SetVertSens = GetVerticalSensitivity() / 2.5f;
//        // add yaw and pitch input to controller
//        AddControllerYawInput(LookAxisVector.X);
//        if (bEnableSensitivityChanges)
//        {
//            AddControllerPitchInput(LookAxisVector.Y * SetVertSens);
//        }
//        else
//        {
//            AddControllerPitchInput(LookAxisVector.Y);
//        }
//
//        //TODO: Come back to this to make it so the player's head turns with input
//        InputYaw = LookAxisVector.X * .25f;
//        InputYaw = FMath::Clamp(InputYaw, -15.f, 15.f);
//        
//
//		InputPitch += LookAxisVector.Y;
//		InputPitch = FMath::Clamp(InputPitch, -10.f, 18.f);
//    }
//}
*/
#pragma endregion

void AEclipseRaptureCharacter::Move(const FInputActionValue& Value)
{
    if (!bCanMove) return;
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
    if (!bCanMove) return;

    Super::Jump();
    CurrentMovementState = ECharacterMovementState::ECMS_Jumping;
}


void AEclipseRaptureCharacter::StartSprint()
{
    if (!CanSprint()) return;

    CurrentMovementState = ECharacterMovementState::ECMS_Sprinting;
    GetCharacterMovement()->MaxWalkSpeed = StoredSprintSpeed;
}

void AEclipseRaptureCharacter::EndSprint()
{
    CurrentMovementState = ECharacterMovementState::ECMS_Walking;
    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed; 
}




bool AEclipseRaptureCharacter::CanSprint()
{
    //Make sure player is walking or idle and is moving
    return CurrentMovementState == ECharacterMovementState::ECMS_Walking ||
        CurrentMovementState == ECharacterMovementState::ECMS_Idle ||
		CurrentMovementState != ECharacterMovementState::ECMS_Crouching &&
		CurrentMovementState != ECharacterMovementState::ECMS_Prone &&
		!bIsCrouching && !bIsProning && GetVelocity().Size() > 0;
}
#pragma endregion
