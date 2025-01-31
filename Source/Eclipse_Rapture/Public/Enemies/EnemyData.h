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

#pragma region AI

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	EEnemyAIStates PreferredAIState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | AI")
	EEnemyAIType AIType;

#pragma endregion

#pragma region Weapons

	//List of weapon classes to spawn with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | Weapons")
	TMap<EWeaponClass, TSubclassOf<AWeaponBase>> StartingWeapons;

	//What weapon class should the enemy start the game with?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Data | Weapons")
	EWeaponClass PreferredStartingWeaponClass = EWeaponClass::EWC_Primary;

#pragma endregion

#pragma region Animation

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Enemy Data | Animation")
	TObjectPtr<class UAnimMontage> EquipPrimaryMontage;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Enemy Data | Animation")
	TObjectPtr<class UAnimMontage> EquipSecondaryMontage;

#pragma endregion
};