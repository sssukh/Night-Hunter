// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SukInventoryManagerComponent.generated.h"

class USukItemDefinition;

USTRUCT()
struct FInventoryEntry
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<class USukItemDefinition> Instance = nullptr;

	UPROPERTY()
	uint8 qty;
};

USTRUCT()
struct FInventoryList
{
	GENERATED_BODY()
	
	FInventoryList(UActorComponent* InOwnerComponent=nullptr) : OwnerComponent(InOwnerComponent)
	{}

	USukItemDefinition* AddEntry(TSubclassOf<USukItemDefinition> InItem);

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
	USukInventoryManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION()
	USukItemDefinition* AddItem(TSubclassOf<class USukItemDefinition> InItem);

	UPROPERTY()
	FInventoryList InventoryList;
};
