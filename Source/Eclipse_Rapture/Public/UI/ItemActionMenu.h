// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemActionMenu.generated.h"

class UButton;

UCLASS()
class ECLIPSE_RAPTURE_API UItemActionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Exposed Variables", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Exposed Variables", meta = (ExposeOnSpawn = "true"))
	int32 ClickedIndex;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UCanvasPanel* ActionMenuPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UVerticalBox* ActionMenuVerticalBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	UButton* ActionMenuUseButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	UButton* ActionMenuDropSingleButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	UButton* ActionMenuDropAllButton;
};
