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




void AWeaponBase::Fire_Implementation()
{
   
}
