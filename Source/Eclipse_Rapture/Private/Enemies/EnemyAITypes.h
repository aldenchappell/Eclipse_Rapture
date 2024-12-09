#pragma once

UENUM(BlueprintType)
enum class EnemyAIType : uint8
{
	EAIT_Aggressor UMETA(DisplayName = "Aggressor Enemy"),
	EAIT_Shooter UMETA(DisplayName = "Shooter Enemy"),
	EAIT_Boss UMETA(DisplayName = "Boss Enemy")
};

UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
	EEAS_Idle UMETA(DisplayName = "Idling"),
	EEAS_Patrol UMETA(DisplayName = "Patrolling"),
	EEAS_Pushing UMETA(DisplayName = "Pushing"),
	EEAS_InCombat UMETA(DisplayName = "In Combat"),
	EEAS_InCover UMETA(DisplayName = "In Cover"),
	EEAS_Dead UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EAlertLevel : uint8
{
	EAL_Idle UMETA(DisplayName = "Idle"),
	EAL_Suspicious UMETA(DisplayName = "Suspicious"),
	EAL_Alerted UMETA(DisplayName = "Alerted"),
	EAL_InCombat UMETA(DisplayName = "In Combat")
};