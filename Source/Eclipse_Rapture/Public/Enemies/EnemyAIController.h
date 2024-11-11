// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI | AI Properties")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI | AI Properties")
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI | AI Properties")
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "AI | AI Properties")
	class UBehaviorTreeComponent* BehaviorTreeComponent;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Targets")
	TObjectPtr<class AEclipseRaptureEnemy> OwningEnemy;

	UPROPERTY(BlueprintReadWrite, Category = "AI | Targets")
	TObjectPtr<class AEclipseRaptureCharacter> TargetCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	TObjectPtr<class UAISenseConfig_Hearing> HearingConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float SightRadius = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float LoseSightRadius = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float PeripheralVisionAngleDegrees = 90.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float HearingRange = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float LoseHearingRange = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float AcceptanceRadius = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float TargetDistance = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	bool bIsTargetInSight = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	bool bIsTargetInHearingRange = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	bool bIsTargetInAcceptanceRadius = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	bool bIsTargetInAttackRange = false;
};
