#pragma once

UENUM(BlueprintType)
enum class EnemyAIType : uint8
{
	EAIT_Aggressor UMETA(DisplayName = "Aggressor Enemy"),
	EAIT_Shooter UMETA(DisplayName = "Shooter Enemy"),
	EAIT_Boss UMETA(DisplayName = "Boss Enemy")
};

UENUM(BlueprintType)
enum class EAlertLevel : uint8
{
	EAL_Idle UMETA(DisplayName = "Idle"),
	EAL_Suspicious UMETA(DisplayName = "Suspicious"),
	EAL_Alerted UMETA(DisplayName = "Alerted"),
	EAL_InCombat UMETA(DisplayName = "In Combat")
};