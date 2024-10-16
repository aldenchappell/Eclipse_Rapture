#include "Weapons/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Damageable.h"


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

    CurrentAmmo = MaxAmmo;
    CurrentClipAmmo = ClipSize;  // Initialize with full clip

    if (WeaponClass == EWeaponClass::EWC_Melee)
    {
		WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBoxOverlap);
    }
}

//For melee weapon collision
void AWeaponBase::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    const FVector TraceStart = MeleeBoxTraceStart->GetComponentLocation();
    const FVector TraceEnd = MeleeBoxTraceEnd->GetComponentLocation();
    
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

    //ensure that this weapon is added to ignore actors list
    for (AActor* Actor : ActorsToIgnore)
    {
		IgnoreActors.AddUnique(Actor);
    }

    FHitResult HitInfo;

    UKismetSystemLibrary::BoxTraceSingle(
        GetWorld(),
        TraceStart,
        TraceEnd,
        FVector(5.f, 5.f, 5.f),
        MeleeBoxTraceStart->GetComponentRotation(),
        ETraceTypeQuery::TraceTypeQuery1,
        false,
        ActorsToIgnore,
        EDrawDebugTrace::ForDuration,
        HitInfo,
        true
    );

    UGameplayStatics::ApplyDamage(
		OtherActor,
        Damage,
        GetInstigator()->GetController(),
        this,
        UDamageType::StaticClass()
    );

    if (HitInfo.GetActor())
    {
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
