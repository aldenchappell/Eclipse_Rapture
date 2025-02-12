// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerMain.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"
#include "Items/Components/FlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Interfaces/Unlockable.h"
#include "CharacterTypes.generated.h"
#include "Items/Item.h"
#include "Weapons/WeaponBase.h"
#include "Building/BuildingComponent.h"

APlayerMain::APlayerMain()
{
    //setup melee weapon
    MeleeWeapon->SetRootComponent(GetRootComponent());

    //fov
    AimFOV = DefaultFOV * AimFOVMultiplier;
}

void APlayerMain::BeginPlay()
{
	Super::BeginPlay();

	if (FirstPersonCamera)
    {
        InitialCameraTransform = FirstPersonCamera->GetRelativeTransform();
    }

    /*if (FlashlightComponent)
    {
        if (FlashlightComponent->GetHasFlashlight() && PlayerBodyMesh)
        {
            FlashlightComponent->Attach(PlayerBodyMesh, FName("FlashlightSocket"));
            FlashlightComponent->Enable();
        }
        else
        {
            FlashlightComponent->Disable();
        }
    }*/
}

void APlayerMain::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleHeadbob();
}


#pragma region Setup Input
void APlayerMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Bind Inputs
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        //Movement
        EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerMain::Move);

        //Melee
        //EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Started, this, &APlayerMain::Melee);

        //Swapping Weapons
        EnhancedInputComponent->BindAction(UnarmedAction, ETriggerEvent::Triggered, this, &APlayerMain::EquipUnarmed, true);
        EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Triggered, this, &APlayerMain::EquipPrimaryWeapon, true);
        EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Triggered, this, &APlayerMain::EquipSecondaryWeapon, true);
        EnhancedInputComponent->BindAction(MeleeWeaponAction, ETriggerEvent::Triggered, this, &APlayerMain::EquipMeleeWeapon, true);
    }
}
#pragma endregion


/// <summary>
/// Melee attack function, gets a random section of the melee montage and plays it
/// </summary>
void APlayerMain::Melee()
{
    if (!bCanMelee) return;

    USkeletalMeshComponent* CharacterMesh = GetMesh();
    if (CharacterMesh)
    {
        UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
        if (!AnimInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("AnimInstance is null."))
                return;
        }

        if (!MeleeMontage)
        {
            UE_LOG(LogTemp, Warning, TEXT("Melee Montage is null."))
                return;
        }

        if (CurrentMovementState == ECharacterMovementState::ECMS_Melee)
        {
            UE_LOG(LogTemp, Warning, TEXT("Movement state already melee.."))
                return;

        }

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
}

#pragma region Movement

void APlayerMain::Move(const FInputActionValue& Value)
{
    if (!GetCanMove()) return;

    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {

        // add movement 
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}

void APlayerMain::HandleHeadbob()
{
    //headbob shakesources are invalid
    if (!GetCanMove() || !IdleShake || !WalkShake || !SprintShake) return;

    APlayerController* PlayerController = nullptr;
    if (PlayerController == nullptr)
    {
        PlayerController = Cast<APlayerController>(GetController());
    }

    TSubclassOf<UCameraShakeBase> ShakeSource = nullptr;
    if (PlayerController)
    {
        switch (CurrentMovementState)
        {
        case ECharacterMovementState::ECMS_Idle:
            ShakeSource = IdleShake;
            break;
        case ECharacterMovementState::ECMS_Walking:
            ShakeSource = WalkShake;
            break;
        case ECharacterMovementState::ECMS_Sprinting:
            ShakeSource = SprintShake;
            break;
        default:
            ShakeSource = IdleShake;
            break;
        }
        if (bEnableHeadbobbing && ShakeSource)
        {
            PlayerController->ClientStartCameraShake(
                ShakeSource,
                1.f,
                ECameraShakePlaySpace::CameraLocal);
        }
    }
}

bool APlayerMain::CanSprint()
{
    return
        CurrentStamina > 0 && GetVelocity().Size() > 0 &&
        CurrentMovementState == ECharacterMovementState::ECMS_Walking ||
        CurrentMovementState == ECharacterMovementState::ECMS_Idle ||
        CurrentMovementState != ECharacterMovementState::ECMS_Crouching &&
        CurrentMovementState != ECharacterMovementState::ECMS_Prone &&
        CurrentMovementState != ECharacterMovementState::ECMS_Jumping &&
        CurrentMovementState != ECharacterMovementState::ECMS_Mantling &&
        !bIsCrouching && !bIsProning && !bIsAiming;
}
UBuildingComponent* APlayerMain::GetBuildingComponent_Implementation() const
{
    return nullptr;
}
UStaticMeshComponent* APlayerMain::GetBuildingBlueprintStaticMesh_Implementation() const
{
    return nullptr;
}

#pragma endregion

#pragma region UI
void APlayerMain::SetCrosshairTexture(UTexture2D* Texture)
{
    if (CrosshairTexture2D)
    {
        CrosshairTexture2D = Texture;
    }
}

#pragma endregion