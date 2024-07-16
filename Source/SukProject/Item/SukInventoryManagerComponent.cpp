// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SukInventoryManagerComponent.h"
#include "SukItem.h"

// Sets default values for this component's properties


USukInventoryManagerComponent::USukInventoryManagerComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	, InventoryList(this)
{
}

USukItemDefinition* USukInventoryManagerComponent::AddItem(TSubclassOf<class USukItemDefinition> InItem)
{
	USukItemDefinition* Result = nullptr;
	if (InItem)
	{
		Result = InventoryList.AddEntry(InItem);
	}
	return Result;
}



USukItemDefinition* FInventoryList::AddEntry(TSubclassOf<USukItemDefinition> InItem)
{

	AActor* OwningActor = OwnerComponent->GetOwner();

	FInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<USukItemDefinition>(OwningActor);
	// NewEntry.Instance = InItem;
	return nullptr;
}
