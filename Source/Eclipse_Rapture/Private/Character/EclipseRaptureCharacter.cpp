
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
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

    //setup inventory component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	InventoryComponent->Capacity = 20;

    CharacterType = ECharacterType::ECT_Player;
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



void AEclipseRaptureCharacter::DoMantleTrace(
    float TraceLength, float TraceZOffset, float FallHeightAdjust,
    FVector& MantlePos1, FVector& MantlePos2)
{
    bCanMantle = false;
    //start the trace around eye level(ish)
    FVector TraceStart = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50.f);
    FVector TraceEnd = TraceStart + GetActorForwardVector() * TraceLength;

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    FHitResult InitialHitInfo, SecondaryHitInfo, TertiaryHitInfo, QuaternaryHitInfo;

    // Line Trace to detect object in front of player
    if (UKismetSystemLibrary::LineTraceSingle(
        GetWorld(), TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1,
        false, ActorsToIgnore, EDrawDebugTrace::None, InitialHitInfo, true, FLinearColor::Black))
    {
        // Adjust Z offset based on whether player is falling
        bool IsFalling = GetCharacterMovement()->IsFalling();
        FVector SphereTraceEnd = InitialHitInfo.Location;
        SphereTraceEnd.Z += IsFalling ? FallHeightAdjust : TraceZOffset;

        //Sphere Trace to determine mantle height
        if (UKismetSystemLibrary::SphereTraceSingle(
            GetWorld(), InitialHitInfo.Location, SphereTraceEnd, 10.f,
            ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
            EDrawDebugTrace::ForDuration, SecondaryHitInfo, true, FLinearColor::Gray))
        {
            //Calculate mantle positions
            MantlePos1 = SecondaryHitInfo.ImpactPoint + GetActorForwardVector() * -50.f; //-50
            MantlePos2 = SecondaryHitInfo.ImpactPoint + GetActorForwardVector() * 120.f; //120
            bCanMantle = true;

            //Perform Tertiary Sphere Trace to check for clear space
            FVector TertiaryTraceLocation = MantlePos2 + FVector(0.f, 0.f, 20.f);
            if (UKismetSystemLibrary::SphereTraceSingle(
                GetWorld(), TertiaryTraceLocation, TertiaryTraceLocation, 10.f,
                ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
                EDrawDebugTrace::ForDuration, TertiaryHitInfo, true))
            {
                bCanMantle = false;

                // Validate Mantle Positions
                if ((MantlePos1 == FVector::ZeroVector) || (MantlePos2 == FVector::ZeroVector))
                {
                    bCanMantle = false;
                }
                else
                {
                    // Adjust MantlePos2 based on Tertiary Trace
                    MantlePos2 = TertiaryHitInfo.ImpactPoint + GetActorForwardVector() * 25.f; //50

                    // Perform Final Quad Sphere Trace
                    FVector QuadTraceStart = MantlePos1;
                    FVector QuadTraceEnd = MantlePos2 + FVector(0.f, 0.f, 50.f); //100

                    if (UKismetSystemLibrary::SphereTraceSingle(
                        GetWorld(), QuadTraceStart, QuadTraceEnd, 20.f,
                        ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
                        EDrawDebugTrace::ForDuration, QuaternaryHitInfo, true))
                    {
                        bCanMantle = false;
                    }
                }
            }
            else
            {
                MantlePos2 = TertiaryHitInfo.ImpactPoint + GetActorForwardVector() * 25.f; //50
            }
        }
    }
    else
    {
        bCanMantle = false;
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

        //Call OnEquip on weapon
        NewWeapon->OnEquip();
        NewWeapon->OwningCharacter = this;

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


void AEclipseRaptureCharacter::EquipWeapon_Implementation(AWeaponBase* Weapon)
{
    if (!Weapon)
    {
        UE_LOG(LogTemp, Error, TEXT("EquipWeapon called with a null weapon!"));
        return;
    }

    // Ensure the weapon is attached to the correct socket on the player's mesh
    FName SocketName = Weapon->SocketName;

    switch (CharacterType)
    {
    case ECharacterType::ECT_Player:
        if (PlayerBodyMesh->DoesSocketExist(SocketName))
        {
            Weapon->AttachToComponent(PlayerBodyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
            UE_LOG(LogTemp, Warning, TEXT("Weapon %s attached to socket: %s"), *Weapon->GetName(), *SocketName.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Socket %s does not exist on player mesh!"), *SocketName.ToString());
        }
        break;
    case ECharacterType::ECT_Enemy:
        if (GetMesh()->DoesSocketExist(SocketName))
        {
            Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
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

    //Check for primary weapon in player weapon inventory
    AWeaponBase* PrimaryWeapon = CurrentWeapons.FindRef(EWeaponClass::EWC_Primary);
    if (!PrimaryWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("No primary weapon found!"));
        return;
    }

    SetSwapTimer();

    SwapWeapon(EWeaponClass::EWC_Primary);
    CurrentWeaponAmmo = PrimaryAmmo;

    //Hide the secondary weapon if equipped
    AWeaponBase* SecondaryWeapon = CurrentWeapons.FindRef(EWeaponClass::EWC_Secondary);
    if (SecondaryWeapon)
    {
        SecondaryWeapon->GetWeaponMesh()->SetVisibility(false);
        UE_LOG(LogTemp, Warning, TEXT("Hiding secondary weapon: %s"), *SecondaryWeapon->GetName());
    }


    PrimaryWeapon->GetWeaponMesh()->SetVisibility(true);

    //Update weapon states
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

#pragma region Damageable Interface Implementations

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

void AEclipseRaptureCharacter::DropItems_Implementation(const TArray<TSubclassOf<class AItem>>& InventoryItems)
{
    if (!HealthComponent) return;
    if (InventoryItems.Num() > 0)
    {
        //for (TSubclassOf<AItem> Item : InventoryItems)
        //{
        //	FActorSpawnParameters SpawnParams;
        //	SpawnParams.Owner = GetOwner();
        //	SpawnParams.Instigator = GetOwner()->GetInstigator();
        //	FVector CharacterPosition = GetOwner()->GetActorLocation();
  //          FVector BackpackSpawnOffset = FVector(CharacterPosition.X, CharacterPosition.Y, CharacterPosition.Z + 5.f);

  //          //TODO:
  //          //Once we have a backpack/storage system setup, switch to spawn a backpack with the inventory items specified.
        //	GetWorld()->SpawnActor<AItem>(Item, BackpackSpawnOffset, GetOwner()->GetActorRotation(), SpawnParams);
        //}
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