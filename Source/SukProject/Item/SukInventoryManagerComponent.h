// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SukInventoryManagerComponent.generated.h"

class USukItem;

USTRUCT()
struct FInventoryEntry
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<USukItem> Instance = nullptr;
};

USTRUCT()
struct FInventoryList
{
	GENERATED_BODY()
	
	FInventoryList(UActorComponent* InOwnerComponent=nullptr) : OwnerComponent(InOwnerComponent)
	{}

	USukItem* AddEntry(TSubclassOf<USukItem> InItem);

	UPROPERTY()
	TArray<FInventoryEntry> Entries;
	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUKPROJECT_API USukInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USukInventoryManagerComponent();

	UFUNCTION()
	USukItem* AddItem(TSubclassOf<USukItem> InItem);

	UPROPERTY()
	FInventoryList InventoryList;
};
