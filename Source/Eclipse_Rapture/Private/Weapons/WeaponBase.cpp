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
#include "Items/Components/ItemDataComponent.h"
#define TraceChannel ETraceTypeQuery_
AWeaponBase::AWeaponBase()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
   /* WeaponMesh->SetupAttachment(GetRootComponent());*/
	SetRootComponent(WeaponMesh);

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


void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();
    
    ////should only be true on melee weapons. false by default
    //if (bShouldDoBoxOverlapCheck)
    //{
    //    WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBoxOverlap);
    //}
}

void AWeaponBase::Reload(UInventoryComponent* PlayerInventory)
{
 //   if (!PlayerInventory || !RequiredAmmo) return;

 //   //TODO: Come back here and fix for new inventory system.
 //   // Get the current amount of ammo available in the player's inventory
 //   //int32 InventoryAmmo = PlayerInventory->GetItemAmount(RequiredAmmo);
	//
 //   // Calculate the remaining space in the magazine
 //   int32 AmmoNeeded = MaxMagazineSize - CurrentAmmo;
	////Get the ID of the ammo item
 //   FDataTableRowHandle AmmoRow = RequiredAmmo->GetDefaultObject<AItem>()->DataComponent->ItemID;
	//FName ItemID = AmmoRow.RowName;
 //   int32 InventoryAmmo = 0;

	//const UDataTable* ItemTable = RequiredAmmo->GetDefaultObject<AItem>()->DataComponent->ItemID.DataTable;
 //   if (ItemTable->FindRow<FItemData>(ItemID, TEXT(""), true))
 //   {
 //       for (const FInventorySlotData& Slot : PlayerInventory->InventoryItems)
 //       {
 //           if (Slot.ItemID == ItemID)
 //           {
 //               InventoryAmmo = Slot.Quantity;
 //               break;
 //           }
 //       }


 //       //TODO: Come back here and fix for new inventory system.
 //       // Determine the actual amount of ammo to load (minimum of needed ammo and available inventory ammo)
 //       int32 AmmoToLoad = FMath::Min(AmmoNeeded, InventoryAmmo);

 //       // If there is ammo to load, add it to the current magazine and update the inventory
 //       if (AmmoToLoad > 0)
 //       {
 //           CurrentAmmo += AmmoToLoad;

 //           //    //TODO: Come back here and fix for new inventory system.
 //               // Remove the used ammo from the player's inventory

 //          // PlayerInventory->RemoveFromInventory(ItemID, AmmoToLoad, CurrentAmmo);
 //       }

 //       // Ensure the weapon is ready to fire if there's any ammo in the magazine
 //       SetCanFire(true);
 //   }
 //   else
 //   {
	//	UE_LOG(LogTemp, Warning, TEXT("WeaponBase.cpp/Reload: Ammo item not found in data table."));
 //   }

	
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
void AWeaponBase::Fire_Implementation()
{
   
}
