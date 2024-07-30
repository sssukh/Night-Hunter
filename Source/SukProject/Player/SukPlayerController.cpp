// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SukPlayerController.h"
#include "UI/SukHUDWidget.h"


ASukPlayerController::ASukPlayerController()
{
	static ConstructorHelpers::FClassFinder<USukHUDWidget> SukHUDWidgetRef(TEXT("/Game/UI/WBP_SukHUDWidget.WBP_SukHUDWidget_C"));
	if (SukHUDWidgetRef.Class)
	{
		SukHUDWidgetClass = SukHUDWidgetRef.Class;
	}
}


void ASukPlayerController::AddItem(USukItemInstance* InItem)
{
	bool IsAdded = false;

	for (FItemEntry Entry : ItemList)
	{
		if (Entry.ItemInstance == InItem)
		{
			IsAdded = true;
			++Entry.qty;
		}
	}

	if (!IsAdded)
	{
		FItemEntry newEntry;
		newEntry.ItemInstance = InItem;
		newEntry.qty = 1;
		ItemList.Add(newEntry);
	}
}






void ASukPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	/*SukHUDWidget = CreateWidget<USukHUDWidget>(this, SukHUDWidgetClass);
	if (SukHUDWidget)
	{
		SukHUDWidget->AddToViewport();
	}*/
}
