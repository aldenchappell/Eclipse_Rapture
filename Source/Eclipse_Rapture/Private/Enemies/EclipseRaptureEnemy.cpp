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

void AEclipseRaptureEnemy::CheckHealthState()
{
	if (HealthComponent && HealthComponent->GetCurrentHealth() <= CriticalHealthThreshold)
	{
		bIsInCriticalHealth = true;
		UpdateAIState(EEnemyAIState::EEAS_InCover);
	}
}

void AEclipseRaptureEnemy::UpdateAIState(EEnemyAIState NewState)
{
	CurrentAIState = NewState;
	//TODO: Update behavior tree or animation as needed based on NewState
}

bool AEclipseRaptureEnemy::CanFire()
{
	if (AmmoCount <= 0) return false;

	float HitChance = FMath::FRandRange(0.0f, 100.0f);
	bool bFirstShot = (CurrentAIState != EEnemyAIState::EEAS_InCombat);
	if (bFirstShot) HitChance += FirstShotAccuracyBonus;

	return HitChance <= Accuracy;
}

