#pragma once

#include "Enemies/EnemyAITypes.h"
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EnemyData.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

#pragma region General

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | General")
	EEnemyTypes EnemyType;

#pragma endregion

#pragma region Stats

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | General")
	float EnemyStartingHealth = 100.f;

#pragma endregion

#pragma region AI

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	EEnemyAIStates PreferredAIState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	EEnemyAIType AIType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	int32 TeamNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	float MaxRememberEnemyTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	float WaitTimeBetweenPatrolPoints = 1.f;

#pragma region AI Senses

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float SightRadius = 3000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float LoseSightRadius = 3000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float PeripheralVisionAngleDegrees = 70.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "AI | AI Properties")
	float HearingRange = 1000.f;

#pragma endregion

#pragma endregion

#pragma region Weapons

	//List of weapon classes to spawn with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | Weapons")
	TMap<EWeaponClass, TSubclassOf<AWeaponBase>> StartingWeapons;

	//What weapon class should the enemy start the game with?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | Weapons")
	EWeaponClass PreferredStartingWeaponClass = EWeaponClass::EWC_Primary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | Weapons")
	float WeaponFireRateNerfMultiplier = 1.5f;

#pragma endregion

#pragma region Animation

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Enemy Data | Animation")
	TObjectPtr<class UAnimMontage> EquipPrimaryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Enemy Data | Animation")
	TObjectPtr<class UAnimMontage> EquipSecondaryMontage;

#pragma endregion
};