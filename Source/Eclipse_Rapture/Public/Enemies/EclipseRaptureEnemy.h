#pragma once

#include "Enemies/EnemyAITypes.h"
#include "Character/CharacterTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EclipseRaptureEnemy.generated.h"


class AItem;
UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEclipseRaptureEnemy();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Character Properties")
	ECharacterType CharacterType = ECharacterType::ECT_Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Character Properties")
	TObjectPtr<class UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Character Properties")
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | AI Properties")
	EnemyAIType AIType = EnemyAIType::EAIT_Shooter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | AI Properties")
	EEnemyAIState CurrentAIState = EEnemyAIState::EEAS_Idle;

protected:
	
	virtual void BeginPlay() override;

#pragma region Movement Properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Movement Properties")
	bool bCanMove = true;

	UPROPERTY(BlueprintReadWrite, Category = "Character | Movement Properties")
	ECharacterMovementState CharacterMovementState = ECharacterMovementState::ECMS_Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Movement Properties")
	float StoredWalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Movement Properties")
	float StoredSprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Movement Properties")
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Movement Properties")
	float CrouchSpeed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Movement Properties")
	float SprintSpeed = 450.f;

	UFUNCTION()
	void InitMovementSpeeds();

#pragma endregion

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
