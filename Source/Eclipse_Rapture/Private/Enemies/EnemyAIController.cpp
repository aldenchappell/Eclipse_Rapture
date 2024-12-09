// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"
#include "Enemies/EclipseRaptureEnemy.h"
#include "AIConfig.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Enemies/PatrolPathComponent.h"
#include "Enemies/DespawningComponent.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	//Setup sight sense
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	if (SightConfig)
	{
		SightConfig->SightRadius = SightRadius;
		SightConfig->LoseSightRadius = LoseSightRadius;
		SightConfig->PeripheralVisionAngleDegrees = PeripheralVisionAngleDegrees;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

		AIPerceptionComponent->ConfigureSense(*SightConfig);
	}

	//Setup hearing sense
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	if (HearingConfig)
	{
		HearingConfig->HearingRange = HearingRange;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

		AIPerceptionComponent->ConfigureSense(*HearingConfig);
	}

	DespawnComponent = CreateDefaultSubobject<UDespawningComponent>(TEXT("Despawning Component"));
}


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//if enemy is not assigned already, cast and get a reference now
	if (!OwningEnemy)
	{
		OwningEnemy = Cast<AEclipseRaptureEnemy>(InPawn);
	}
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyAIController::IncreaseAlertValue(float ValueToAdd)
{
	//Increase alert value, clamp between 0 and 100
	SetAlertValue(FMath::Clamp(AlertValue + ValueToAdd, 0.f, 100.f));
}

void AEnemyAIController::UpdateAlertLevel(float AlertIncrease)
{
	AlertValue = FMath::Clamp(AlertValue + AlertIncrease, 0.f, 100.f);
	if (AlertValue >= 100.f) CurrentAlertLevel = EAlertLevel::EAL_InCombat;
	else if (AlertValue >= 50.f) CurrentAlertLevel = EAlertLevel::EAL_Alerted;
	else if (AlertValue >= 20.f) CurrentAlertLevel = EAlertLevel::EAL_Suspicious;
	else CurrentAlertLevel = EAlertLevel::EAL_Idle;

	//TODO: Implement corresponding behaviors or state changes based on CurrentAlertLevel
}
