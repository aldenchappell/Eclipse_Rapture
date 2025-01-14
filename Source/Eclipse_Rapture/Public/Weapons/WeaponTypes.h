#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_Unarmed UMETA(DisplayName = "Unarmed"),
	EWT_Secondary UMETA(DisplayName = "Secondary"),
	EWT_Primary UMETA(DisplayName = "Primary"),
	EWT_Melee UMETA(DisplayName = "Melee"),
	//EWT_Shotgun UMETA(DisplayName = "Shotgun"),
};

UENUM(BlueprintType)
enum class EWeaponFireMode : uint8
{
	EWFM_SemiAuto UMETA(DisplayName = "Semi-Auto"),
	EWFM_Automatic UMETA(DisplayName = "Automatic"),
	EWFM_BurstFire UMETA(DisplayName = "Burst Fire"),
};

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	EWN_Unarmed UMETA(DisplayName = "Unarmed"), 
	EWN_CombatKnife UMETA(DisplayName = "Combat Knife"),
	EWN_Bat UMETA(DisplayName = "Baseball Bat"),
	EWN_Baton UMETA(DisplayName = "Baton"),
	EWN_M1911 UMETA(DisplayName = "M1911"), 
	EWN_Glock UMETA(DisplayName = "Glock"),
	EWN_Magnum UMETA(DisplayName = "Magnum"),
	EWN_M4 UMETA(DisplayName = "M4"),
	EWN_AR15 UMETA(DisplayName = "AR-15"),
	EWN_Ak47 UMETA(DisplayName = "AK-47"),
	EWN_Benelli UMETA(DisplayName = "Benelli M4"),
	EWN_Remington UMETA(DisplayName = "Remington 870")
};

UENUM(BlueprintType)
enum class EWeaponClass : uint8
{
	EWC_Unarmed UMETA(DisplayName = "Unarmed"),
	EWC_Primary UMETA(DisplayName = "Primary"),
	EWC_Secondary UMETA(DisplayName = "Secondary"),
	EWC_Melee UMETA(DisplayName = "Melee")
};

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	EAT_9mm UMETA(DisplayName = "9mm"),
	EAT_45 UMETA(DisplayName = ".45mm"),
	EAT_357 UMETA(DisplayName = ".357mm"),
	EAT_556 UMETA(DisplayName = "5.56mm"),
	EAT_762 UMETA(DisplayName = "7.62mm"),
	EAT_12Gauge UMETA(DisplayName = "12 Gauge"),
	EAT_Slug UMETA(DisplayName = "Shotgun Slug"),
	EAT_Rocket UMETA(DisplayName = "Rocket")
};

