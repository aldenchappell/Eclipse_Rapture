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

	// Initialize the perception component
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// Create and configure the sight sense
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

	// Create and configure the hearing sense
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	if (HearingConfig)
	{
		HearingConfig->HearingRange = HearingRange;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

		AIPerceptionComponent->ConfigureSense(*HearingConfig);
	}

	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());

	PatrolPathComponent = CreateDefaultSubobject<UPatrolPathComponent>(TEXT("Path Following Component"));

	DespawnComponent = CreateDefaultSubobject<UDespawningComponent>(TEXT("Despawning Component"));
}


void AEnemyAIController::BeginPlay()
{
	InitializeEnemyType();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	//if enemy is not assigned already, cast and get a reference now
	if (!OwningEnemy)
	{
		OwningEnemy = Cast<AEclipseRaptureEnemy>(InPawn);
	}
}

void AEnemyAIController::OnUnPossess()
{

}

void AEnemyAIController::InitializeEnemyType()
{
	if (OwningEnemy)
	{
		switch (OwningEnemy->AIType)
		{
			case EnemyAIType::EAIT_Aggressor:
				AIPerceptionComponent->SetDominantSense(HearingConfig->GetSenseImplementation());
				break;
			case EnemyAIType::EAIT_Shooter:
				AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
				break;
			default:
				AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
				UE_LOG(LogTemp, Warning, TEXT("No AI Type assigned to %s, defaulting to Shooter"), *OwningEnemy->GetName());
				break;
		}
	}
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
