#include "Enemies/EclipseRaptureEnemy.h"
#include "Weapons/WeaponBase.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"
#include "Enemies/EnemyAITypes.h"

AEclipseRaptureEnemy::AEclipseRaptureEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set the character type to Enemy
    CharacterType = ECharacterType::ECT_Enemy;
}

void AEclipseRaptureEnemy::BeginPlay()
{
    Super::BeginPlay();

    // Validate weapon configuration
    if (!IsValidWeaponConfiguration())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid weapon configuration for %s. No weapons will be assigned."), *GetName());
        return;
    }

    // Spawn and equip starting weapons
    //SpawnStartingWeapons();

    //// Equip the starting weapon
    //EquipStartingWeapon();
}

void AEclipseRaptureEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AEclipseRaptureEnemy::IsValidWeaponConfiguration() const
{
    // Ensure no more than one primary and one secondary weapon
    int32 PrimaryCount = 0;
    int32 SecondaryCount = 0;

    for (const auto& WeaponPair : StartingWeapons)
    {
        if (WeaponPair.Key == EWeaponClass::EWC_Primary)
        {
            PrimaryCount++;
        }
        else if (WeaponPair.Key == EWeaponClass::EWC_Secondary)
        {
            SecondaryCount++;
        }
    }

    return PrimaryCount <= 1 && SecondaryCount <= 1;
}

void AEclipseRaptureEnemy::EquipStartingWeapon()
{
    // Ensure the CurrentWeapons map is populated
    if (CurrentWeapons.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has no weapons in the CurrentWeapons map."), *GetName());
        return;
    }

    // Equip the primary weapon if available
    if (CurrentWeapons.Contains(EWeaponClass::EWC_Primary) && CurrentWeapons[EWeaponClass::EWC_Primary])
    {
        EquipWeapon(CurrentWeapons[EWeaponClass::EWC_Primary]);
        return;
    }

    // Equip the secondary weapon if no primary is available
    if (CurrentWeapons.Contains(EWeaponClass::EWC_Secondary) && CurrentWeapons[EWeaponClass::EWC_Secondary])
    {
        EquipWeapon(CurrentWeapons[EWeaponClass::EWC_Secondary]);
        return;
    }

    // Log if no valid weapons are found
    UE_LOG(LogTemp, Warning, TEXT("%s has no valid weapons to equip."), *GetName());
}

void AEclipseRaptureEnemy::AddWeapon(TSubclassOf<AWeaponBase> WeaponClass, EWeaponClass WeaponSlot)
{
    if (!WeaponClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid WeaponClass provided for %s."), *GetName());
        return;
    }

    // Spawn the weapon
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    AWeaponBase* SpawnedWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, SpawnParams);
    if (SpawnedWeapon)
    {
        // Attach to the skeletal mesh
        FName SocketName = SpawnedWeapon->SocketName;
        if (GetMesh()->DoesSocketExist(SocketName))
        {
            SpawnedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
        }

        // Initialize weapon properties
        SpawnedWeapon->OwningActor = this;

        // Add to CurrentWeapons map
        CurrentWeapons.Add(WeaponSlot, SpawnedWeapon);
        OnEquipWeapon.Broadcast();
        UE_LOG(LogTemp, Log, TEXT("%s added weapon %s to slot %d."), *GetName(), *SpawnedWeapon->GetName(), static_cast<int32>(WeaponSlot));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s failed to spawn weapon for slot %d."), *GetName(), static_cast<int32>(WeaponSlot));
    }
}

void AEclipseRaptureEnemy::SpawnStartingWeapons()
{
    for (const auto& WeaponPair : StartingWeapons)
    {
        AddWeapon(WeaponPair.Value, WeaponPair.Key);
    }
}

FVector AEclipseRaptureEnemy::GetAdjustedAimDirection(const FVector& OriginalDirection) const
{
    // Calculate deviation based on accuracy
    float Deviation = (100.0f - Accuracy) / 100.0f; // Higher deviation for lower accuracy

    // Generate random offset
    float RandomX = FMath::FRandRange(-Deviation, Deviation);
    float RandomY = FMath::FRandRange(-Deviation, Deviation);
    float RandomZ = FMath::FRandRange(-Deviation, Deviation);

    FVector AdjustedDirection = OriginalDirection + FVector(RandomX, RandomY, RandomZ);
    return AdjustedDirection.GetSafeNormal(); // Normalize the vector to maintain direction
}


bool AEclipseRaptureEnemy::CanFire()
{
    if (AmmoCount <= 0) return false;

    float HitChance = FMath::FRandRange(0.0f, 100.0f);
    bool bFirstShot = (CurrentAIState != EEnemyAIState::EEAS_InCombat);
    if (bFirstShot) HitChance += FirstShotAccuracyBonus;

    return HitChance <= Accuracy;
}

#if WITH_EDITOR
void AEclipseRaptureEnemy::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (PropertyChangedEvent.Property &&
        PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(AEclipseRaptureEnemy, StartingWeapons))
    {
        if (!IsValidWeaponConfiguration())
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid weapon configuration in editor: Only one Primary and one Secondary weapon allowed."));
        }
    }
}
#endif
