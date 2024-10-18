

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
#include "UI/AmmoCounterWComponent.h"

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

	MeleeWeapon->SetRootComponent(GetRootComponent());
}

void AEclipseRaptureCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;
}


void AEclipseRaptureCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEclipseRaptureCharacter::HandleCrouch(float DeltaTime)
{
    //Handle crouching interpolation
    float CrouchInterpTime = FMath::Min(1.f, CrouchEntranceSpeed * DeltaTime);
    CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
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

        //Interact
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::Interact);

        //Aim
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::StartAiming);
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AEclipseRaptureCharacter::StopAiming);

        //Melee
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Started, this, &AEclipseRaptureCharacter::Melee);
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

        //UE_LOG(LogTemp, Warning, TEXT("Started aiming with weapon class: %s"), *UEnum::GetValueAsString(CurrentWeaponClass));
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


/// <summary>
/// Melee attack function, gets a random section of the melee montage and plays it
/// </summary>
void AEclipseRaptureCharacter::Melee()
{
    if (!bCanMelee) return;

    UAnimInstance* AnimInstance = PlayerBodyMesh->GetAnimInstance();
	if (AnimInstance && MeleeMontage && CurrentMovementState != ECharacterMovementState::ECMS_Melee)
	{
        UE_LOG(LogTemp, Warning, TEXT("Starting melee attack."));
		AnimInstance->Montage_Play(MeleeMontage);

		const int32 RandomMeleeSection = FMath::RandRange(0, 1);
        FName SectionName = FName();

        switch (RandomMeleeSection)
        {
		case 0:
			SectionName = FName("Melee_1");
			break;
		case 1:
			SectionName = FName("Melee_2");
            break;
		default: 
            UE_LOG(LogTemp, Warning, TEXT("EclipseRaptureCharacter.cpp/Melee error when trying to play melee montage."));
            SectionName = FName("Melee_1");
			break;
        }
		AnimInstance->Montage_JumpToSection(SectionName, MeleeMontage);
        CurrentMovementState = ECharacterMovementState::ECMS_Melee;
	}
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("EclipseRaptureCharacter.cpp/Melee error when trying to start melee attack."));
    }
}

void AEclipseRaptureCharacter::SpawnItem_Implementation(TSubclassOf<AWeaponBase> WeaponToSpawn)
{
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

#pragma region Movement




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

void AEclipseRaptureCharacter::SetAmmo()
{
    if (CurrentWeapons.FindRef(CurrentWeaponClass) != nullptr)
    {
        CurrentWeaponAmmo--;
        switch (CurrentWeaponName)
        {
        case EWeaponName::EWN_Pistol_A:
            SecondaryAmmo = CurrentWeaponAmmo;
            break;
        case EWeaponName::EWN_Pistol_B:
            SecondaryAmmo = CurrentWeaponAmmo;
            break;
		case EWeaponName::EWN_Rifle_A:
			PrimaryAmmo = CurrentWeaponAmmo;
            break;
        case EWeaponName::EWN_Rifle_B:
			PrimaryAmmo = CurrentWeaponAmmo;
            break;
        default:
            if (GEngine)
            {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error setting ammo."));
            }
            break;
        }
    }
}

bool AEclipseRaptureCharacter::CanSprint()
{
    return 
        CurrentStamina > 0 && GetVelocity().Size() > 0 &&
        CurrentMovementState == ECharacterMovementState::ECMS_Walking ||
        CurrentMovementState == ECharacterMovementState::ECMS_Idle ||
		CurrentMovementState != ECharacterMovementState::ECMS_Crouching &&
		CurrentMovementState != ECharacterMovementState::ECMS_Prone &&
		!bIsCrouching && !bIsProning;
}
#pragma endregion
