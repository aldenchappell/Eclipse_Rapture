

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

        //Swapping Weapons
        EnhancedInputComponent->BindAction(UnarmedAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::EquipUnarmed);
        EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::EquipPrimaryWeapon);
        EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &AEclipseRaptureCharacter::EquipSecondaryWeapon);
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

void AEclipseRaptureCharacter::SwapWeapon(EWeaponClass NewWeaponClass)
{
    UE_LOG(LogTemp, Warning, TEXT("Attempting to swap to weapon class: %d"), static_cast<int32>(NewWeaponClass));

    // If the new weapon is already equipped, exit early
    if (CurrentWeaponClass == NewWeaponClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon class %d is already equipped."), static_cast<int32>(NewWeaponClass));
        return;
    }

    // Handle switching to unarmed
    if (NewWeaponClass == EWeaponClass::EWC_Unarmed)
    {
        EquipUnarmed();
        return;
    }

    // Check if the new weapon exists in the inventory
    AWeaponBase* NewWeapon = CurrentWeapons.FindRef(NewWeaponClass);
    if (NewWeapon)
    {
        // Safely detach the current weapon (if any)
        if (CurrentWeapon)
        {
            UE_LOG(LogTemp, Warning, TEXT("Detaching current weapon: %s"), *CurrentWeapon->GetName());
            CurrentWeapon->SetActorHiddenInGame(true);
            CurrentWeapon->SetActorEnableCollision(false);
            CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        }

        // Equip the new weapon
        EquipWeapon(NewWeapon);
        CurrentWeaponClass = NewWeaponClass;

        // Update the UI or ammo logic
        OnWeaponUpdateSetAmmo();
        
		UAnimInstance* AnimInstance = PlayerBodyMesh->GetAnimInstance();
        if (AnimInstance && CurrentWeapon->EquipMontage)
        {
            AnimInstance->Montage_Play(CurrentWeapon->EquipMontage);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Weapon class %d not found in inventory!"), static_cast<int32>(NewWeaponClass));
    }
}


void AEclipseRaptureCharacter::EquipWeapon(AWeaponBase* Weapon)
{
    if (!Weapon)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeapon called with a null weapon!"));
        return;
    }

    // Ensure the weapon is attached to the correct socket on the player's mesh
    FName SocketName = Weapon->SocketName;
    if (PlayerBodyMesh->DoesSocketExist(SocketName))
    {
        Weapon->AttachToComponent(PlayerBodyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
        UE_LOG(LogTemp, Warning, TEXT("Weapon %s attached to socket: %s"), *Weapon->GetName(), *SocketName.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Socket %s does not exist on player mesh!"), *SocketName.ToString());
    }

    // Ensure the weapon is visible and collision is enabled
    Weapon->SetActorHiddenInGame(false);
    Weapon->SetActorEnableCollision(true);
    Weapon->GetWeaponMesh()->SetVisibility(true, true);  // Force visibility

    // Store the reference to the currently equipped weapon
    CurrentWeapon = Weapon;
}

AWeaponBase* AEclipseRaptureCharacter::GetCurrentWeaponByClass(EWeaponClass WeaponClass)
{
    // Retrieve the weapon instance from the CurrentWeapons map
    return CurrentWeapons.Contains(WeaponClass) ? CurrentWeapons[WeaponClass] : nullptr;
}

void AEclipseRaptureCharacter::EquipUnarmed()
{
    UE_LOG(LogTemp, Warning, TEXT("Equipping Unarmed."));

	if (CurrentWeapons.FindRef(EWeaponClass::EWC_Primary))
	{
		USkeletalMeshComponent* WeaponMesh = CurrentWeapons.FindRef(EWeaponClass::EWC_Primary)->GetWeaponMesh();
        if (WeaponMesh)
        {
            WeaponMesh->SetVisibility(false);
        }
	}

    if (CurrentWeapons.FindRef(EWeaponClass::EWC_Secondary))
    {
        USkeletalMeshComponent* WeaponMesh = CurrentWeapons.FindRef(EWeaponClass::EWC_Secondary)->GetWeaponMesh();
        if (WeaponMesh)
        {
            WeaponMesh->SetVisibility(false);
        }
    }

    SetSwapTimer();
	
    CurrentWeaponClass = EWeaponClass::EWC_Unarmed;
    CurrentWeaponType = EWeaponType::EWT_Unarmed;
    CurrentWeaponName = EWeaponName::EWN_Unarmed;

    UE_LOG(LogTemp, Warning, TEXT("Successfully equipped Unarmed."));
}

void AEclipseRaptureCharacter::EquipPrimaryWeapon()
{
    if (!bCanSwapWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon swap on cooldown!"));
        return;
    }

    // Find the primary weapon in the inventory
    AWeaponBase* PrimaryWeapon = CurrentWeapons.FindRef(EWeaponClass::EWC_Primary);
    if (!PrimaryWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("No primary weapon found!"));
        return;
    }

    // Remove redundant check for already equipped primary weapon
    SetSwapTimer();  // Start the cooldown timer

    // Proceed with swapping to the primary weapon
    SwapWeapon(EWeaponClass::EWC_Primary);
    CurrentWeaponAmmo = PrimaryAmmo;

    // Hide the secondary weapon if equipped
    AWeaponBase* SecondaryWeapon = CurrentWeapons.FindRef(EWeaponClass::EWC_Secondary);
    if (SecondaryWeapon)
    {
        SecondaryWeapon->GetWeaponMesh()->SetVisibility(false);
    }

    // Ensure the primary weapon is visible
    PrimaryWeapon->GetWeaponMesh()->SetVisibility(true);

    // Update the weapon state
    CurrentWeaponClass = EWeaponClass::EWC_Primary;
    CurrentWeaponType = EWeaponType::EWT_Primary;
    CurrentWeaponName = PrimaryWeapon->GetWeaponName();
    CurrentWeaponBase = PrimaryWeapon;

    UE_LOG(LogTemp, Warning, TEXT("Swapped to primary weapon: %s"), *PrimaryWeapon->GetName());
}






void AEclipseRaptureCharacter::EquipSecondaryWeapon()
{
    if (!bCanSwapWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon swap on cooldown!"));
        return;
    }

    AWeaponBase* SecondaryWeapon = CurrentWeapons.FindRef(EWeaponClass::EWC_Secondary);
    if (!SecondaryWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("No secondary weapon found! Cannot swap to secondary."));
        return;
    }

    if (CurrentWeapon && CurrentWeapon->GetWeaponType() == EWeaponType::EWT_Secondary)
    {
        UE_LOG(LogTemp, Warning, TEXT("Secondary weapon already equipped!"));
        return;
    }

    SetSwapTimer();

    SwapWeapon(EWeaponClass::EWC_Secondary);
    CurrentWeaponAmmo = SecondaryAmmo;

    AWeaponBase* PrimaryWeapon = CurrentWeapons.FindRef(EWeaponClass::EWC_Primary);
    if (PrimaryWeapon)
    {
        PrimaryWeapon->GetWeaponMesh()->SetVisibility(false);
    }

    SecondaryWeapon->GetWeaponMesh()->SetVisibility(true);
    CurrentWeaponClass = EWeaponClass::EWC_Secondary;
    CurrentWeaponType = EWeaponType::EWT_Secondary;
    CurrentWeaponName = SecondaryWeapon->GetWeaponName();

    CurrentWeaponBase = SecondaryWeapon;

    UE_LOG(LogTemp, Warning, TEXT("Swapped to secondary weapon: %s"), *SecondaryWeapon->GetName());
}


void AEclipseRaptureCharacter::ResetSwap()
{
    bCanSwapWeapon = true;
    UE_LOG(LogTemp, Warning, TEXT("Weapon swap ready."));
}

void AEclipseRaptureCharacter::SetSwapTimer()
{
    bCanSwapWeapon = false;
    GetWorld()->GetTimerManager().SetTimer(WeaponSwapTimerHandle, this, &AEclipseRaptureCharacter::ResetSwap, WeaponSwapCooldown, false);
}

void AEclipseRaptureCharacter::StartAiming()
{
    AWeaponBase* Weapon = CurrentWeapons.FindRef(CurrentWeaponClass);
    if (Weapon)
    {
        CurrentMovementState = ECharacterMovementState::ECMS_Aiming;
        GetCharacterMovement()->MaxWalkSpeed = AimMovementSpeed;
        bIsAiming = true;

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
        bIsAiming = false;

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

void AEclipseRaptureCharacter::OnWeaponUpdateSetAmmo()
{
    if (CurrentWeapons.FindRef(CurrentWeaponClass) != nullptr)
    {
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
