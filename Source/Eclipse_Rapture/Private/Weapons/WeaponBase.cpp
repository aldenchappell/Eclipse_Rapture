#include "Weapons/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Damageable.h"
#include "Items/Ammo/AmmoBase.h"
#include "Character/InventoryComponent.h"
#include "DrawDebugHelpers.h" 
#include "Items/WeaponPickup.h"

#define TraceChannel ETraceTypeQuery_
AWeaponBase::AWeaponBase()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
    WeaponMesh->SetupAttachment(GetRootComponent());

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
    WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    
	MeleeBoxTraceStart = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTraceStart"));
    MeleeBoxTraceStart->SetupAttachment(GetRootComponent());

	MeleeBoxTraceEnd = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTraceEnd"));
    MeleeBoxTraceEnd->SetupAttachment(GetRootComponent());   
}


void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = MaxMagazineSize;

    //should only be true on melee weapons. false by default
    if (bShouldDoBoxOverlapCheck)
    {
        WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBoxOverlap);
    }
}

void AWeaponBase::Reload(UInventoryComponent* PlayerInventory)
{
    if (!PlayerInventory || !RequiredAmmo) return;

    // Get the current amount of ammo available in the player's inventory
    int32 InventoryAmmo = PlayerInventory->GetItemAmount(RequiredAmmo);

    // Calculate the remaining space in the magazine
    int32 AmmoNeeded = MaxMagazineSize - CurrentAmmo;

    // Determine the actual amount of ammo to load (minimum of needed ammo and available inventory ammo)
    int32 AmmoToLoad = FMath::Min(AmmoNeeded, InventoryAmmo);

    // If there is ammo to load, add it to the current magazine and update the inventory
    if (AmmoToLoad > 0)
    {
        CurrentAmmo += AmmoToLoad;

        // Remove the used ammo from the player's inventory
        PlayerInventory->RemoveItemAmount(RequiredAmmo, AmmoToLoad);
    }

    // Ensure the weapon is ready to fire if there's any ammo in the magazine
    SetCanFire(true);
}


//For melee weapon collision
void AWeaponBase::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //debug to see what is getting hit
    if (GEngine)
    {
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Black, FString("Hit: ") + OtherActor->GetName(), false);
    }

    //start and end points for the box trace
    const FVector TraceStart = MeleeBoxTraceStart->GetComponentLocation();
    const FVector TraceEnd = MeleeBoxTraceEnd->GetComponentLocation();

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    //ensure that this weapon is added to the ignore actors list
    for (AActor* Actor : ActorsToIgnore)
    {
        IgnoreActors.AddUnique(Actor);
    }

    FHitResult HitInfo;
	FVector BoxHalfSize = WeaponBox->GetScaledBoxExtent(); //WeaponBox half size

	//box trace to see if we hit anything
    bool GotHit = UKismetSystemLibrary::BoxTraceSingle(
        GetWorld(),
        TraceStart,
        TraceEnd,
        BoxHalfSize,
        MeleeBoxTraceStart->GetComponentRotation(),
        ETraceTypeQuery::TraceTypeQuery1,
        false,
        ActorsToIgnore,
        EDrawDebugTrace::Persistent,
        HitInfo,
        true
    );

	//UE_LOG(LogTemp, Warning, TEXT("Box X size: $d"), *BoxHalfSize.X.ToString());
    //UE_LOG(LogTemp, Warning, TEXT("Box Y size: $d"), *BoxHalfSize.Y.ToString());
    //UE_LOG(LogTemp, Warning, TEXT("Box Z size: $d"), *BoxHalfSize.Z.ToString());
    //If we hit something, apply damage
    if (GotHit && HitInfo.GetActor())
    {
        UGameplayStatics::ApplyDamage(
            OtherActor,
            Damage,
            GetInstigator()->GetController(),
            this,
            UDamageType::StaticClass()
        );

        IDamageable* DamageableActor = Cast<IDamageable>(HitInfo.GetActor());

        if (DamageableActor)
        {
            DamageableActor->Execute_TakeDamage(HitInfo.GetActor(), Damage, HitInfo.ImpactPoint);
        }
        IgnoreActors.AddUnique(HitInfo.GetActor());
    }
}

UTexture2D* AWeaponBase::GetThumbnailTexture()
{
    if (PickupClass)
    {
        const AWeaponPickup* PickupDefault = PickupClass->GetDefaultObject<AWeaponPickup>();
        if (PickupDefault)
        {
            return PickupDefault->ThumbnailTexture;
        }
    }
    return nullptr;
}


/// <summary>
/// Implements the fire function for the weapon(Line trace("raycast") is handled in blueprint.
/// </summary>
void AWeaponBase::Fire_Implementation()
{
   
}
