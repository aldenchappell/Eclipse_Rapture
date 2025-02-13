// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemies/EnemyAITypes.h"
#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class ECLIPSE_RAPTURE_API AEnemyAIController : public ADetourCrowdAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	UFUNCTION(BlueprintCallable, Category = "AI | AI Functions")
	void SetupSenses();
	//UPROPERTY(BlueprintReadWrite, Category = "AI | AI Properties")
	//int32 CurrentPatrolPoint = 0;

	//UFUNCTION(BlueprintCallable, Category = "AI | AI Functions")
	//void IncreaseAlertValue(float ValueToAdd);

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Alert System")
	//EAlertLevel CurrentAlertLevel = EAlertLevel::EAL_Idle;

	////Adjust alert level based on stimulus
	//UFUNCTION(BlueprintCallable, Category = "AI | Alert System")
	//void UpdateAlertLevel(float AlertIncrease); 

#pragma region Blackboard Keys

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Blackboard Keys")
	FName Key_AttackTarget = "AttackTarget";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Blackboard Keys")
	FName Key_State = "StateKeyName";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Blackboard Keys")
	FName Key_PointOfInterest = "PointOfInterest";*/

		/*	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Blackboard Keys")
	FName

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Blackboard Keys")
	FName

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Blackboard Keys")
	FName*/

#pragma endregion

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

#pragma region Character References
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | Targets")
	TObjectPtr<class AEclipseRaptureEnemy> OwningEnemy;

	/*UPROPERTY(BlueprintReadWrite, Category = "AI | Targets")
	TObjectPtr<class AEclipseRaptureCharacter> TargetCharacter;*/

#pragma endregion

#pragma region AI Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI | AI Properties")
	TObjectPtr<class UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	TObjectPtr<class UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	TObjectPtr<class UAISenseConfig_Hearing> HearingConfig;


#pragma endregion

	
private:

	

public:


};
