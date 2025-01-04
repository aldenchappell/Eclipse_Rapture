// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetItem.h"

void UWidgetItem::SetItem(AItem* NewItem)
{
	Item = NewItem;
}

void UWidgetItem::SetItemData(FItemData Data)
{
	ItemData = Data;
}
