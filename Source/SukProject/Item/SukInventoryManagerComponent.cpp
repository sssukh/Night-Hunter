// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukInventoryManagerComponent.h"
#include "SukItem.h"

// Sets default values for this component's properties
USukInventoryManagerComponent::USukInventoryManagerComponent()
{
	
	// ...
}

USukItem* USukInventoryManagerComponent::AddItem(TSubclassOf<USukItem> InItem)
{
	USukItem* Item = nullptr;

	return nullptr;
}

USukItem* FInventoryList::AddEntry(TSubclassOf<USukItem> InItem)
{
	USukItem* Item = nullptr;

	AActor* OwningActor = OwnerComponent->GetOwner();

	FInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<USukItem>(OwningActor);

	return nullptr;
}
