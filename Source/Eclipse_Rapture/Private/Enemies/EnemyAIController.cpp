// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"
#include "Enemies/EclipseRaptureEnemy.h"
#include "AIConfig.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Enemies/PatrolPathComponent.h"
#include "Enemies/EnemyData.h"

AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyAIController::SetupSenses()
{
	UE_LOG(LogTemp, Warning, TEXT("SetupSenses() called in AEnemyAIController"));

	if (!AIPerceptionComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("SetupSenses() failed: AIPerceptionComponent is nullptr"));
		return;
	}

	if (!OwningEnemy)
	{
		UE_LOG(LogTemp, Error, TEXT("SetupSenses() failed: OwningEnemy is nullptr"));
		return;
	}

	FEnemyData EnemyData = OwningEnemy->GetEnemyData();

	// Retrieve sight configuration
	UAISenseConfig_Sight* ConfigSight = AIPerceptionComponent->GetSenseConfig<UAISenseConfig_Sight>();
	if (ConfigSight)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully retrieved SightConfig"));

		// Set dynamic sight values
		float LoseRange = ConfigSight->LoseSightRadius - ConfigSight->SightRadius;
		ConfigSight->SightRadius = EnemyData.SightRadius;
		ConfigSight->LoseSightRadius = ConfigSight->SightRadius + LoseRange;
		ConfigSight->PeripheralVisionAngleDegrees = EnemyData.PeripheralVisionAngleDegrees;

		// Debug log updated sight values
		UE_LOG(LogTemp, Warning, TEXT("Updated Sight Config: SightRadius = %f, LoseSightRadius = %f, PeripheralVisionAngle = %f"),
			   ConfigSight->SightRadius, ConfigSight->LoseSightRadius, ConfigSight->PeripheralVisionAngleDegrees);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetupSenses() failed: Could not retrieve SightConfig"));
	}

	// Retrieve hearing configuration
	UAISenseConfig_Hearing* ConfigHearing = AIPerceptionComponent->GetSenseConfig<UAISenseConfig_Hearing>();
	if (ConfigHearing)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully retrieved HearingConfig"));

		// Set dynamic hearing values
		ConfigHearing->HearingRange = EnemyData.HearingRange;

		// Debug log updated hearing values
		UE_LOG(LogTemp, Warning, TEXT("Updated Hearing Config: HearingRange = %f"), ConfigHearing->HearingRange);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SetupSenses() failed: Could not retrieve HearingConfig"));
	}

	// Ensure AI Perception updates immediately
	AIPerceptionComponent->RequestStimuliListenerUpdate();
	UE_LOG(LogTemp, Warning, TEXT("AI Perception settings updated"));
}


//void AEnemyAIController::IncreaseAlertValue(float ValueToAdd)
//{
//	//Increase alert value, clamp between 0 and 100
//	SetAlertValue(FMath::Clamp(AlertValue + ValueToAdd, 0.f, 100.f));
//}
//
//void AEnemyAIController::UpdateAlertLevel(float AlertIncrease)
//{
//	AlertValue = FMath::Clamp(AlertValue + AlertIncrease, 0.f, 100.f);
//	if (AlertValue >= 100.f) CurrentAlertLevel = EAlertLevel::EAL_InCombat;
//	else if (AlertValue >= 50.f) CurrentAlertLevel = EAlertLevel::EAL_Alerted;
//	else if (AlertValue >= 20.f) CurrentAlertLevel = EAlertLevel::EAL_Suspicious;
//	else CurrentAlertLevel = EAlertLevel::EAL_Idle;
//
//	//TODO: Implement corresponding behaviors or state changes based on CurrentAlertLevel
//}
