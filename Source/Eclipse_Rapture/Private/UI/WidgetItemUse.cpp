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

    //TODO: Come back and add item use icon to itemdata struct
    // Set the thumbnail
   /* if (UseThumbnail)
    {
        if (Item->ItemUseIcon)
        {
            UseThumbnail->SetBrushFromTexture(Item->ItemUseIcon);
        }
        else if (DebugPlaceholderTexture)
        {
            UseThumbnail->SetBrushFromTexture(DebugPlaceholderTexture);
        }
    }*/

    //TODO: Come back and add item use icon to itemdata struct
    // Set the main item use description
    //if (ItemUseText)
    //{
    //    FString MainDescription = UEnum::GetDisplayValueAsText(Item->GetItemData().MainItemUseDescriptionType).ToString();
    //    ItemUseText->SetText(FText::FromString(MainDescription));
    //}

    //// Set the main impact type
    //if (ItemImpactText)
    //{
    //    FString ImpactDescription = UEnum::GetDisplayValueAsText(Item->GetItemData().UseImpactType).ToString();
    //    ItemImpactText->SetText(FText::FromString(ImpactDescription));
    //}
}
