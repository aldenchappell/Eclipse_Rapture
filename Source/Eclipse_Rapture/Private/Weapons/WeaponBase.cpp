#include "Weapons/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Damageable.h"


#include "DrawDebugHelpers.h" //for debug drawing functions

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

void AWeaponBase::Reload(AWeaponBase* WeaponToReload, float InventoryAmmo)
{
    if (WeaponToReload->WeaponClass == EWeaponClass::EWC_Melee) return;

	CurrentAmmo = MaxMagazineSize;

    if (GEngine)
    {
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Black, FString("Ammo after reloading"), false);
    }
    //TODO: Uncomment this once inventory is setup.
	/*if (InventoryAmmo > 0)
	{
		if (InventoryAmmo >= MaxMagazineSize)
		{
			CurrentAmmo = MaxMagazineSize;
			InventoryAmmo -= MaxMagazineSize;
		}
		else
		{
			CurrentAmmo = InventoryAmmo;
			InventoryAmmo = 0;
		}
        SetCanFire(true);
	}*/
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


/// <summary>
/// Implements the fire function for the weapon(Line trace("raycast") is handled in blueprint.
/// </summary>
void AWeaponBase::Fire_Implementation()
{
   
}
