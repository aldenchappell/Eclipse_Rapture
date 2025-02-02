// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/MeleeWeaponBase.h"
#include "Components/BoxComponent.h"

AMeleeWeaponBase::AMeleeWeaponBase()
{
    WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
    WeaponBox->SetupAttachment(WeaponMesh);
    WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    WeaponBox->SetCollisionResponseToAllChannels(ECR_Overlap);
    WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

    MeleeBoxTraceStart = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTraceStart"));
    MeleeBoxTraceStart->SetupAttachment(WeaponMesh);

    MeleeBoxTraceEnd = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTraceEnd"));
    MeleeBoxTraceEnd->SetupAttachment(WeaponMesh);
}

void AMeleeWeaponBase::StartMeleeAttack_Implementation()
{
}

void AMeleeWeaponBase::EndMeleeAttack_Implementation()
{
}

//
////For melee weapon collision
//void AWeaponBase::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//    //debug to see what is getting hit
//    if (GEngine)
//    {
//		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Black, FString("Hit: ") + OtherActor->GetName(), false);
//    }
//
//    //start and end points for the box trace
//    const FVector TraceStart = MeleeBoxTraceStart->GetComponentLocation();
//    const FVector TraceEnd = MeleeBoxTraceEnd->GetComponentLocation();
//
//    TArray<AActor*> ActorsToIgnore;
//    ActorsToIgnore.Add(this);
//
//    //ensure that this weapon is added to the ignore actors list
//    for (AActor* Actor : ActorsToIgnore)
//    {
//        IgnoreActors.AddUnique(Actor);
//    }
//
//    FHitResult HitInfo;
//	FVector BoxHalfSize = WeaponBox->GetScaledBoxExtent(); //WeaponBox half size
//
//	//box trace to see if we hit anything
//    bool GotHit = UKismetSystemLibrary::BoxTraceSingle(
//        GetWorld(),
//        TraceStart,
//        TraceEnd,
//        BoxHalfSize,
//        MeleeBoxTraceStart->GetComponentRotation(),
//        ETraceTypeQuery::TraceTypeQuery1,
//        false,
//        ActorsToIgnore,
//        EDrawDebugTrace::Persistent,
//        HitInfo,
//        true
//    );
//
//    //If we hit something, apply damage
//    if (GotHit && HitInfo.GetComponent())
//    {
//        UGameplayStatics::ApplyDamage(
//            OtherActor,
//            Damage,
//            GetInstigator()->GetController(),
//            this,
//            UDamageType::StaticClass()
//        );
//
//        IDamageable* DamageableComponent = Cast<IDamageable>(HitInfo.GetComponent());
//
//        if (DamageableComponent)
//        {
//            DamageableComponent->Execute_TakeDamage(HitInfo.GetComponent(), Damage, HitInfo.ImpactPoint);
//        }
//        IgnoreActors.AddUnique(HitInfo.GetActor());
//    }
//}

/// <summary>
/// Implements the fire function for the weapon(Line trace("raycast") is handled in blueprint.
/// </summary>


