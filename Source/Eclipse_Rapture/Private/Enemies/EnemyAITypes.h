#pragma once

UENUM(BlueprintType)
enum class EEnemyTypes : uint8
{
	EET_Humanoid UMETA(DisplayName = "Humanoid"),
	EET_DemonicHumanoid UMETA(DisplayName = "Demonic Humanoid"),
	EET_HumanoidBoss UMETA(DisplayName = "Humanoid Boss"),
	EET_DemonicBoss UMETA(DisplayName = "Demonic Boss")
};

UENUM(BlueprintType)
enum class EEnemyAIType : uint8
{
	EAIT_Aggressor UMETA(DisplayName = "Aggressor Enemy"), //melee enemies
	EAIT_Shooter UMETA(DisplayName = "Shooter Enemy"), //ranged enemies
	EAIT_Boss UMETA(DisplayName = "Boss Enemy") //boss enemies
};

UENUM(BlueprintType)
enum class EEnemyAIStates : uint8
{
	EEAS_Frozen UMETA(DisplayName = "Frozen"),
	EEAS_Idle UMETA(DisplayName = "Idle"),
	EEAS_RoamPassive UMETA(DisplayName = "Roam Passive"),
	EEAS_RoamAggressive UMETA(DisplayName = "Roam Aggressive"),
	EEAS_PatrolPassive UMETA(DisplayName = "Patrol Passive"),
	EEAS_PatrolAggressive UMETA(DisplayName = "Patrol Aggressive"),
	EEAS_Follow UMETA(DisplayName = "Follow"),
	EEAS_Flee UMETA(DisplayName = "Flee"),
	EEAS_Attack UMETA(DisplayName = "Attack"),
	EEAS_Investigate UMETA(DisplayName = "Investigate"),
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