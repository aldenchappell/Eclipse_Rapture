#pragma once

#include "Character/EclipseRaptureCharacter.h"
#include "Enemies/EnemyAITypes.h"
#include "Character/CharacterTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EclipseRaptureEnemy.generated.h"


class AItem;
UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureEnemy : public AEclipseRaptureCharacter
{
	GENERATED_BODY()

public:
	AEclipseRaptureEnemy();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | AI Properties")
	EnemyAIType AIType = EnemyAIType::EAIT_Shooter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | AI Properties")
	EEnemyAIState CurrentAIState = EEnemyAIState::EEAS_Idle;

protected:
	
	virtual void BeginPlay() override;

#pragma region Weapons

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons")
	TSubclassOf<class AWeaponBase> CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons")
	float MinAmmoToHold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapons")
	float MaxAmmoToHold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	float Accuracy = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	float FirstShotAccuracyBonus = 20.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	float AmmoCount = 30.0f;

	bool CanFire();

	
#pragma endregion

#pragma region Items

	//Items to drop when the enemy is killed
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Character | Items")
	TArray<TSubclassOf<AItem>> ItemsToDrop;
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float CriticalHealthThreshold = 30.0f; // Threshold to trigger a retreat or cover state

	UPROPERTY(BlueprintReadWrite, Category = "Health")
	bool bIsInCriticalHealth = false;

	void CheckHealthState();
	void UpdateAIState(EEnemyAIState NewState);

private:

public:
};
