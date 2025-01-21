#include "UI/WidgetInventory.h"
#include "UI/WidgetItemTooltip.h"


void UWidgetInventory::ResetCreatedTooltips()
{
	if (CreatedTooltips.Num() <= 0) return;

	for (UWidgetItemTooltip* Tooltip : CreatedTooltips)
	{
		if (Tooltip)
		{
			Tooltip->RemoveFromParent();
			Tooltip = nullptr;
            CreatedTooltips.Empty();
		}
	}
}

void UWidgetInventory::NativeConstruct()
{
    Super::NativeConstruct();
}