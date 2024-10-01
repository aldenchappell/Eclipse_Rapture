#include "Weapons/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"

AWeaponBase::AWeaponBase()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(GetRootComponent());
}

void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = MaxAmmo;
    CurrentClipAmmo = ClipSize;  // Initialize with full clip
}

/// <summary>
/// Implements the fire function for the weapon(Line trace(raycast) is handled in blueprint.
/// </summary>
void AWeaponBase::Fire_Implementation()
{
   // if (bCanFire && CurrentClipAmmo > 0)
   // {
   //     // Decrease the ammo in the current clip
   //     CurrentClipAmmo--;

   //     UE_LOG(LogTemp, Warning, TEXT("Shot fired. Ammo left in clip: %d"), CurrentClipAmmo);

   //     if (FireAnimation)
   //     {
			//WeaponMesh->PlayAnimation(FireAnimation, false);
   //     }

   //     // Check if the clip is empty
   //     if (CurrentClipAmmo <= 0)
   //     {
   //         bCanFire = false;

   //         if (OutOfAmmoSound)
   //         {
   //             UGameplayStatics::PlaySoundAtLocation(this, OutOfAmmoSound, GetActorLocation());
   //         }
   //     }
   // }
}
