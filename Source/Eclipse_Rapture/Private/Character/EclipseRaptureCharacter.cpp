

#include "Character/EclipseRaptureCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/WeaponBase.h"
#include "UI/AmmoCounterWComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetEclipseRaptureCharacter.h"
#include "Components/Image.h" 
#include "Kismet/KismetMathLibrary.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"
#include "Items/Components/FlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Interfaces/Unlockable.h"
#include "Building/BuildingComponent.h"
#include "Weapons/RangedWeaponBase.h"
#include "Weapons/MeleeWeaponBase.h"

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

    bIsAiming = false;

	//setup health component
	//HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

    CharacterType = ECharacterType::ECT_Player;
}

void AEclipseRaptureCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;
}

void AEclipseRaptureCharacter::SetBuildingBlueprintVisibility_Implementation(bool bNewVisibility)
{
	/*if (BuildingComponent)
	{
		
	}*/
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
        EquipUnarmed(false);
        return;
    }

    // Check if the new weapon exists in the inventory
    AWeaponBase* NewWeapon = CurrentWeapon;
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

        //Call OnEquip on weapon
        NewWeapon->OnEquip();
        NewWeapon->OwningCharacter = this;

        // Update the UI or ammo logic
        OnWeaponUpdateSetAmmo();

        USkeletalMeshComponent* CharacterMesh = GetMesh();

        if (CharacterMesh)
        {
            UAnimInstance* AnimInstance = CharacterMesh->GetAnimInstance();
            if (AnimInstance && CurrentWeapon->GetWeaponData().EquipMontage)
            {
                AnimInstance->Montage_Play(CurrentWeapon->GetWeaponData().EquipMontage);
            }
        }
        

        SetBuildingBlueprintVisibility(false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Weapon class %d not found in inventory!"), static_cast<int32>(NewWeaponClass));
    }
}


void AEclipseRaptureCharacter::EquipWeapon_Implementation(AWeaponBase* Weapon)
{
    if (!Weapon)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeapon called with a null weapon!"));
        return;
    }

    // Ensure the weapon is attached to the correct socket on the player's mesh
    USkeletalMeshComponent* CharacterMesh = GetMesh();
    FName SocketName = Weapon->GetWeaponData().SocketName;

    if (CharacterMesh)
    {
        switch (CharacterType)
        {
        case ECharacterType::ECT_Player:
            if (CharacterMesh->DoesSocketExist(SocketName))
            {
                Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
                UE_LOG(LogTemp, Warning, TEXT("Weapon %s attached to socket: %s"), *Weapon->GetName(), *SocketName.ToString());
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Socket %s does not exist on player mesh!"), *SocketName.ToString());
            }
            break;
        case ECharacterType::ECT_Enemy:
            if (CharacterMesh->DoesSocketExist(SocketName))
            {
                Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
                UE_LOG(LogTemp, Warning, TEXT("Weapon %s attached to socket: %s"), *Weapon->GetName(), *SocketName.ToString());
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Socket %s does not exist on enemy mesh!"), *SocketName.ToString());
            }
            break;
        }

        // Ensure the weapon is visible and collision is enabled
        Weapon->SetActorHiddenInGame(false);
        Weapon->SetActorEnableCollision(true);
        Weapon->GetWeaponMesh()->SetVisibility(true, true);  // Force visibility

        // Store the reference to the currently equipped weapon
        CurrentWeapon = Weapon;
    }

   
}

void AEclipseRaptureCharacter::EquipUnarmed(bool EnforceTimer)
{
    UE_LOG(LogTemp, Warning, TEXT("Equipping Unarmed."));

    if (PrimaryWeapon && PrimaryWeapon->GetWeaponMesh())
    {
        PrimaryWeapon->GetWeaponMesh()->SetVisibility(false);
    }

    if (SecondaryWeapon && SecondaryWeapon->GetWeaponMesh())
    {
        SecondaryWeapon->GetWeaponMesh()->SetVisibility(false);
    }

    if (MeleeWeapon && MeleeWeapon->GetWeaponMesh())
    {
        MeleeWeapon->GetWeaponMesh()->SetVisibility(false);
    }
	
    if (EnforceTimer)
    {
        SetSwapTimer();
    }
   

    CurrentWeaponClass = EWeaponClass::EWC_Unarmed;
    CurrentWeaponType = EWeaponType::EWT_Unarmed;
    CurrentWeaponName = EWeaponName::EWN_Unarmed;
	CurrentWeapon = nullptr;

    UE_LOG(LogTemp, Warning, TEXT("Successfully equipped Unarmed."));
}

void AEclipseRaptureCharacter::EquipPrimaryWeapon(bool EnforceTimer)
{
    if (!bCanSwapWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon swap on cooldown!"));
        return;
    }

    if (!PrimaryWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("No primary weapon found!"));
        return;
    }

    if (EnforceTimer)
    {
        SetSwapTimer();
    }

    SwapWeapon(EWeaponClass::EWC_Primary);
    CurrentWeaponAmmo = PrimaryAmmo;

    if (SecondaryWeapon)
    {
        SecondaryWeapon->GetWeaponMesh()->SetVisibility(false);
        UE_LOG(LogTemp, Warning, TEXT("Hiding secondary weapon: %s"), *SecondaryWeapon->GetName());
    }

    if (MeleeWeapon)
    {
		MeleeWeapon->GetWeaponMesh()->SetVisibility(false);
		UE_LOG(LogTemp, Warning, TEXT("Hiding melee weapon: %s"), *MeleeWeapon->GetName());
    }


    PrimaryWeapon->GetWeaponMesh()->SetVisibility(true);

    //Update weapon states
    CurrentWeaponClass = EWeaponClass::EWC_Primary;
    CurrentWeaponType = EWeaponType::EWT_Primary;
	CurrentWeaponName = PrimaryWeapon->GetWeaponData().WeaponNameType;


    CurrentWeapon = PrimaryWeapon;

    UE_LOG(LogTemp, Warning, TEXT("Swapped to primary weapon: %s"), *PrimaryWeapon->GetName());
}

void AEclipseRaptureCharacter::EquipSecondaryWeapon(bool EnforceTimer)
{
    if (!bCanSwapWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon swap on cooldown!"));
        return;
    }

    if (!SecondaryWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("No secondary weapon found! Cannot swap to secondary."));
        return;
    }

    if (EnforceTimer)
    {
        SetSwapTimer();
    }

    SwapWeapon(EWeaponClass::EWC_Secondary);
    CurrentWeaponAmmo = SecondaryAmmo;

    /*AWeaponBase* PrimaryWeapon = CurrentWeapons.FindRef(EWeaponClass::EWC_Primary);*/
    if (PrimaryWeapon)
    {
        PrimaryWeapon->GetWeaponMesh()->SetVisibility(false);
    }

    if (MeleeWeapon)
    {
        MeleeWeapon->GetWeaponMesh()->SetVisibility(false);
        UE_LOG(LogTemp, Warning, TEXT("Hiding melee weapon: %s"), *MeleeWeapon->GetName());
    }

    SecondaryWeapon->GetWeaponMesh()->SetVisibility(true);
    CurrentWeaponClass = EWeaponClass::EWC_Secondary;
    CurrentWeaponType = EWeaponType::EWT_Secondary;
    CurrentWeaponName = SecondaryWeapon->GetWeaponData().WeaponNameType;

    CurrentWeapon = SecondaryWeapon;

    UE_LOG(LogTemp, Warning, TEXT("Swapped to secondary weapon: %s"), *SecondaryWeapon->GetName());
}

void AEclipseRaptureCharacter::EquipMeleeWeapon(bool EnforceTimer)
{
    if (!bCanSwapWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon swap on cooldown!"));
        return;
    }

    if (!MeleeWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("No melee weapon found! Cannot swap to melee."));
        return;
    }

    if (CurrentWeaponClass == EWeaponClass::EWC_Melee)
    {
        UE_LOG(LogTemp, Warning, TEXT("Melee weapon is already equipped."));
        return;
    }


    if (EnforceTimer)
    {
        SetSwapTimer();
    }

    SwapWeapon(EWeaponClass::EWC_Melee);
    CurrentWeaponAmmo = -1;

    // Hide other weapons
    if (PrimaryWeapon)
    {
        PrimaryWeapon->GetWeaponMesh()->SetVisibility(false);
    }

    if (SecondaryWeapon)
    {
        SecondaryWeapon->GetWeaponMesh()->SetVisibility(false);
    }

    // Equip melee weapon
    MeleeWeapon->GetWeaponMesh()->SetVisibility(true);
    CurrentWeaponClass = EWeaponClass::EWC_Melee;
    CurrentWeaponType = EWeaponType::EWT_Melee;
    CurrentWeaponName = MeleeWeapon->GetWeaponData().WeaponNameType;
    CurrentWeapon = MeleeWeapon;

    UE_LOG(LogTemp, Warning, TEXT("Swapped to melee weapon: %s"), *MeleeWeapon->GetName());
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

void AEclipseRaptureCharacter::OnWeaponUpdateSetAmmo()
{
   /* if (CurrentWeapons.FindRef(CurrentWeaponClass) != nullptr)
    {*/
        /*switch (CurrentWeaponName)
        {
		case EWeaponName::EWN_Unarmed:
			break;
		case EWeaponName::EWN_CombatKnife:
			break;
		case EWeaponName::EWN_Bat:
			break;
		case EWeaponName::EWN_Baton:
			break;
        case EWeaponName::EWN_M1911:
            SecondaryAmmo = CurrentWeaponAmmo;
            break;
        case EWeaponName::EWN_Glock:
            SecondaryAmmo = CurrentWeaponAmmo;
            break;
		case EWeaponName::EWN_Magnum:
			SecondaryAmmo = CurrentWeaponAmmo;
			break;
        case EWeaponName::EWN_AR15:
            PrimaryAmmo = CurrentWeaponAmmo;
            break;
        case EWeaponName::EWN_M4A1:
            PrimaryAmmo = CurrentWeaponAmmo;
            break;
		case EWeaponName::EWN_AK47:
			PrimaryAmmo = CurrentWeaponAmmo;
			break;
		case EWeaponName::EWN_Remington:
			PrimaryAmmo = CurrentWeaponAmmo;
            break;
		case EWeaponName::EWN_BenelliM4:
			PrimaryAmmo = CurrentWeaponAmmo;
            break;
		case EWeaponName::EWN_HuntingRifle:
			PrimaryAmmo = CurrentWeaponAmmo;
			break;*/

        //default:
        //    if (GEngine)
        //    {
        //        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error setting ammo."));
        //    }
        //    break;
        //}
    //}
}


UInventoryComponent* AEclipseRaptureCharacter::GetInventoryComponentRef_Implementation()
{
    return nullptr;
}

UHealthComponent* AEclipseRaptureCharacter::GetHealthComponentRef_Implementation()
{
    return nullptr;
}

FVector AEclipseRaptureCharacter::GetAdjustedAimDirection(const FVector& OriginalDirection) const
{
    // Calculate deviation based on accuracy
    float Deviation = (100.0f - Accuracy) / 100.0f; // Higher deviation for lower accuracy
    UE_LOG(LogTemp, Warning, TEXT("Deviation: %f"), Deviation);

    // Generate a random deviation angle in radians
    float MaxAngle = Deviation * PI / 4; // Scale to a maximum cone angle (e.g., 45 degrees when Deviation is 1)
    float RandomAngle = FMath::FRandRange(0.0f, MaxAngle);
    float RandomYaw = FMath::FRandRange(0.0f, 2 * PI); // Full rotation around the yaw axis

    // Convert the random spherical coordinates to Cartesian coordinates
    FVector RandomOffset = FVector(
        FMath::Sin(RandomAngle) * FMath::Cos(RandomYaw),
        FMath::Sin(RandomAngle) * FMath::Sin(RandomYaw),
        FMath::Cos(RandomAngle)
    );

    // Align the offset with the original direction
    FVector AdjustedDirection = OriginalDirection + RandomOffset;
    return AdjustedDirection.GetSafeNormal(); // Normalize the vector to maintain direction
}

#pragma region Interface Implementations

void AEclipseRaptureCharacter::TakeDamage_Implementation(FDamageInfo DamageInfo)
{
    if (!HealthComponent) return;
    if (HealthComponent->GetCurrentHealth() > 0)
    {
        float TargetHealth = HealthComponent->GetCurrentHealth() - DamageInfo.DamageAmount;

        UGameplayStatics::ApplyDamage(GetOwner(), DamageInfo.DamageAmount, nullptr, nullptr, nullptr);
        HealthComponent->SetCurrentHealth(
            FMath::Lerp(HealthComponent->GetCurrentHealth(),
            TargetHealth,
            1.5f));


        if (HealthComponent->GetCurrentHealth() <= 0)
        {
            HealthComponent->SetCurrentHealth(0);
            HealthComponent->OnDeathEvent.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("%s is now dead"), *GetOwner()->GetName());
        }
    }
}

float AEclipseRaptureCharacter::GetMaxHealth_Implementation()
{
    if (!HealthComponent) return 0 ;
    return HealthComponent->MaxHealth;
}

float AEclipseRaptureCharacter::GetCurrentHealth_Implementation()
{
    if (!HealthComponent) return 0;

    return HealthComponent->GetCurrentHealth();
}

float AEclipseRaptureCharacter::GetCriticalHealthThreshold_Implementation()
{
	if (!HealthComponent) return 0;
    return HealthComponent->CriticalHealthThreshold;
}


#pragma endregion