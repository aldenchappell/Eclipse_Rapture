

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

    //Setup crouching
    CrouchEyeOffset = FVector(0.f);
    CrouchEntranceSpeed = 12.f;

    //Setup proning
    ProneEyeOffset = FVector(0.f);
    ProneEntranceSpeed = 2.f;
    ProneEyeHeightZ = -50.f;
}

void AEclipseRaptureCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;
}

void AEclipseRaptureCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Determine the target FOV based on the current movement state
    float TargetFOV = (CurrentMovementState == ECharacterMovementState::ECMS_Sprinting) ? SprintFOV : DefaultFOV;

    //Lerp the FOV between current and target FOV
    FirstPersonCamera->FieldOfView = FMath::FInterpTo(FirstPersonCamera->FieldOfView, TargetFOV, DeltaTime, 5.0f); // 5.0f is the interpolation speed

    //Handle crouching interpolation
    float CrouchInterpTime = FMath::Min(1.f, CrouchEntranceSpeed * DeltaTime);
    CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
}

void AEclipseRaptureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Bind Inputs
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        //Movement
        EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Move);

		//Looking **MOVED TO BLUEPRINT**
        //EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Look);

        //Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::StopJumping);

        //Crouching (Toggled)
        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::ToggleCrouch);

        //Sprinting
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::StartSprint);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::EndSprint);

        //Proning (Toggled)
        EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::ToggleProne);

        //Interact
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Interact);
    }
}
void AEclipseRaptureCharacter::Interact()
{
    if (CurrentOverlappingItem && CurrentOverlappingItem->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
    {
        // Call the Execute_Interact function for the interface
        IInteractInterface::Execute_Interact(CurrentOverlappingItem, this);
    }
}


void AEclipseRaptureCharacter::SpawnItem_Implementation(TSubclassOf<UWeaponBase> WeaponToSpawn, FVector PickupLocation)
{
}

#pragma region Movement

void AEclipseRaptureCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
    if (HalfHeightAdjust == 0.f) return;

    float StartBaseEyeHeight = BaseEyeHeight;
    Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
    CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;

    if (FirstPersonCamera)
    {
        FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
    }
    
}

void AEclipseRaptureCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
    if (HalfHeightAdjust == 0.f) return;

    float StartBaseEyeHeight = BaseEyeHeight;
    Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
    CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;

    if (FirstPersonCamera)
    {
        FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
    }
    
}

void AEclipseRaptureCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
    if (FirstPersonCamera)
    {
        FirstPersonCamera->GetCameraView(DeltaTime, OutResult);
        OutResult.Location += CrouchEyeOffset;
    }
}
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
    CurrentMovementState = ECharacterMovementState::ECMS_Jumping;
}





void AEclipseRaptureCharacter::StartCrouch()
{
    if (CurrentMovementState == ECharacterMovementState::ECMS_Sprinting) return;  // Prevent crouching while sprinting

    Crouch();
    GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeedCrouched;
    CurrentMovementState = ECharacterMovementState::ECMS_Crouching;
}

void AEclipseRaptureCharacter::EndCrouch()
{
    UnCrouch();
    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;

    if (GetVelocity().Size() > 0)
    {
        CurrentMovementState = ECharacterMovementState::ECMS_Walking;
    }
    else
    {
        CurrentMovementState = ECharacterMovementState::ECMS_Idle;
    }
}

void AEclipseRaptureCharacter::ToggleCrouch()
{
    //Check if the player is already crouching
    if (CurrentMovementState == ECharacterMovementState::ECMS_Crouching)
    {
        EndCrouch();
    }
    else
    {
        StartCrouch();
    }
}



void AEclipseRaptureCharacter::StartProne()
{
    if (CurrentMovementState == ECharacterMovementState::ECMS_Sprinting || CurrentMovementState == ECharacterMovementState::ECMS_Crouching) return;

    //Enter prone state
    GetCharacterMovement()->MaxWalkSpeed = ProneMovementSpeed;
    CurrentMovementState = ECharacterMovementState::ECMS_Prone;

    //Transition to prone eye offset
    ProneEyeOffset.Z = ProneEyeHeightZ; //this value dictates the Z position of the camera when entering the prone position

    if(FirstPersonCamera)
    {
        FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, ProneEyeOffset.Z), false);
    }
}

void AEclipseRaptureCharacter::EndProne()
{
    //Exit prone state and return to walking speed and state
    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;
    CurrentMovementState = ECharacterMovementState::ECMS_Walking;

    //Transition to default eye offset
    ProneEyeOffset.Z = 0.f;

	if (FirstPersonCamera)
	{
		FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
	}
}


void AEclipseRaptureCharacter::ToggleProne()
{
    if (CurrentMovementState == ECharacterMovementState::ECMS_Prone)
    {
        EndProne();
    }
    else
    {
        StartProne();
    }
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
    return CurrentMovementState == ECharacterMovementState::ECMS_Walking &&
        GetVelocity().Size() > 0;  //Make sure player is moving
}

#pragma endregion
