// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"
#include "Enemies/EclipseRaptureEnemy.h"
#include "AIConfig.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"

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
		HearingConfig->bUseLoSHearing = true;
		HearingConfig->LoSHearingRange = LoseHearingRange;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;

		AIPerceptionComponent->ConfigureSense(*HearingConfig);
	}

	// Set up the perception component to use the configured senses
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());


}


void AEnemyAIController::BeginPlay()
{

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
