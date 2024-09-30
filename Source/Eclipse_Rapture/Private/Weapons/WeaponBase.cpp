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

void AWeaponBase::Fire_Implementation()
{
    if (bCanFire && CurrentClipAmmo > 0)
    {
        // Decrease the ammo in the current clip
        CurrentClipAmmo--;

        UE_LOG(LogTemp, Warning, TEXT("Shot fired! Ammo left in clip: %d"), CurrentClipAmmo);

        if (FireAnimation)
        {
			WeaponMesh->PlayAnimation(FireAnimation, false);
        }

        // Play Shoot Sound
        if (ShootSound)
        {
            UGameplayStatics::PlaySoundAtLocation(this, ShootSound, GetActorLocation());
        }

        // Check if the clip is empty
        if (CurrentClipAmmo <= 0)
        {
            bCanFire = false;  // Prevent further shooting until reloaded
            UE_LOG(LogTemp, Warning, TEXT("Clip empty! Cannot fire anymore until reloaded."));

            // Optionally, trigger reload or play out-of-ammo sound
            if (OutOfAmmoSound)
            {
                UGameplayStatics::PlaySoundAtLocation(this, OutOfAmmoSound, GetActorLocation());
            }
        }
    }
    else if (CurrentClipAmmo <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot fire! Out of ammo in the clip."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot fire! `bCanFire` is set to false."));
    }
}
