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
#include "Weapons/Components/WeaponDataComponent.h"
#include "Weapons/WeaponData.h"

#define TraceChannel ETraceTypeQuery_
AWeaponBase::AWeaponBase()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponDataComponent = CreateDefaultSubobject<UWeaponDataComponent>(TEXT("Weapon Data"));
}


void AWeaponBase::BeginPlay()
{
    Super::BeginPlay();
}

FDataTableRowHandle AWeaponBase::GetWeaponID_Implementation()
{
    return FDataTableRowHandle();
}

FWeaponData AWeaponBase::GetWeaponData_Implementation()
{
    return FWeaponData();
}

void AWeaponBase::Fire_Implementation()
{
   
}
