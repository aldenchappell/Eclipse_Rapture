#include "UI/WidgetItemUse.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Item.h"
#include "Items/ItemObject.h"
void UWidgetItemUse::SetItemUseDetails(AItem* Item)
{
    if (!Item)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetItemUseDetails: Item is null."));
        return;
    }

    // Set the thumbnail
    if (UseThumbnail)
    {
        if (Item->GetItemObject()->GetItemUseIcon())
        {
            UseThumbnail->SetBrushFromTexture(Item->GetItemObject()->GetItemUseIcon());
        }
        else if (DebugPlaceholderTexture)
        {
            UseThumbnail->SetBrushFromTexture(DebugPlaceholderTexture);
        }
    }

    // Set the main item use description
    if (ItemUseText)
    {
        FString MainDescription = UEnum::GetDisplayValueAsText(Item->GetItemObject()->GetMainItemUseDescriptionType()).ToString();
        ItemUseText->SetText(FText::FromString(MainDescription));
    }

    // Set the main impact type
    if (ItemImpactText)
    {
        FString ImpactDescription = UEnum::GetDisplayValueAsText(Item->GetItemObject()->GetUseImpactType()).ToString();
        ItemImpactText->SetText(FText::FromString(ImpactDescription));
    }
}
