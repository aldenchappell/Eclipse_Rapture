UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	EUT_Wood UMETA(DisplayName = "Wood"),
	EUT_Brick UMETA(DisplayName = "Brick"),
	EUT_Metal UMETA(DisplayName = "Sheet Metal"),
	EUT_Reinforced UMETA(DisplayName = "Reinforced Material")
};