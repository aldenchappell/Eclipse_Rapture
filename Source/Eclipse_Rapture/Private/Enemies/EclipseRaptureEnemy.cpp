// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EclipseRaptureEnemy.h"
#include "Character/CharacterTypes.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"



AEclipseRaptureEnemy::AEclipseRaptureEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterType = ECharacterType::ECT_Enemy;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AEclipseRaptureEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitMovementSpeeds();
}

void AEclipseRaptureEnemy::InitMovementSpeeds()
{
	StoredWalkSpeed = WalkSpeed;
	StoredSprintSpeed = SprintSpeed;
}

void AEclipseRaptureEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}