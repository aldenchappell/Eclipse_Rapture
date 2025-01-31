#include "Enemies/EclipseRaptureEnemy.h"
#include "Weapons/WeaponBase.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"
#include "Enemies/EnemyAITypes.h"
#include "Weapons/RangedWeaponBase.h"
#include "Weapons/MeleeWeaponBase.h"
#include "Enemies/Components/EnemyDataComponent.h"
#include "Enemies/EnemyData.h"

AEclipseRaptureEnemy::AEclipseRaptureEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set the character type to Enemy
    CharacterType = ECharacterType::ECT_Enemy;

	EnemyData = CreateDefaultSubobject<UEnemyDataComponent>(TEXT("Enemy Data"));
}

void AEclipseRaptureEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void AEclipseRaptureEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEclipseRaptureEnemy::EquipStartingWeapon()
{
    if (!PrimaryWeapon)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has no weapons in the CurrentWeapons map."), *GetName());
        return;
    }

    if (PrimaryWeapon)
    {
        EquipWeapon(PrimaryWeapon);
        return;
    }
    
    // Equip the secondary weapon if no primary is available
    if (SecondaryWeapon)
    {
        EquipWeapon(SecondaryWeapon);
        return;
    }

    if (MeleeWeapon)
    {
        EquipWeapon(MeleeWeapon);
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
        FName SocketName = SpawnedWeapon->GetWeaponData().SocketName;
        if (GetMesh()->DoesSocketExist(SocketName))
        {
            SpawnedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
        }

        // Initialize weapon properties
        SpawnedWeapon->OwningCharacter = this;

        CurrentWeapon = SpawnedWeapon;
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
    for (const auto& WeaponPair : GetEnemyData().StartingWeapons)
    {
        AddWeapon(WeaponPair.Value, WeaponPair.Key);
    }
}

FEnemyData AEclipseRaptureEnemy::GetEnemyData_Implementation()
{
    return FEnemyData();
}
FDataTableRowHandle AEclipseRaptureEnemy::GetEnemyID_Implementation()
{
    return FDataTableRowHandle();
}