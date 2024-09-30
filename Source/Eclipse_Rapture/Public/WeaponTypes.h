#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_Unarmed UMETA(DisplayName = "Unarmed"),
	EWT_Melee UMETA(DisplayName = "Melee"),
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_Rifle UMETA(DisplayName = "Rifle")
	//EWT_Shotgun UMETA(DisplayName = "Shotgun"),
	//EWT_Sniper UMETA(DisplayName = "Sniper")
};

UENUM(BlueprintType)
enum class EWeaponFireMode : uint8
{
	EWFM_SemiAuto UMETA(DisplayName = "Semi-Auto"),
	EWFM_Automatic UMETA(DisplayName = "Automatic")
};

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	EWN_Unarmed UMETA(DisplayName = "Unarmed"),
	EWN_Melee UMETA(DisplayName = "Melee"),
	EWN_Pistol_A UMETA(DisplayName = "Pistol_A"),
	EWN_Pistol_B UMETA(DisplayName = "Pistol_B"),
	EWN_Rifle_A UMETA(DisplayName = "Rifle_A"),
	EWN_Rifle_B UMETA(DisplayName = "Rifle_B")
	//EWN_Shotgun UMETA(DisplayName = "Shotgun"),
	//EWN_Sniper UMETA(DisplayName = "Sniper")
};

UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
	EWC_Unarmed UMETA(DisplayName = "Unarmed"),
	EWC_Melee UMETA(DisplayName = "Melee"),
	EWC_Primary UMETA(DisplayName = "Primary"),
	EWC_Secondary UMETA(DisplayName = "Secondary"),
};

