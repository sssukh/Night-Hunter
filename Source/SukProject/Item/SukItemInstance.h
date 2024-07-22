// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "SukItemInstance.generated.h"

USTRUCT(BlueprintType)
struct FItemEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USukItemInstance> ItemInstance;

	UPROPERTY(BlueprintReadWrite)
	uint8 qty = 0;
};

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukItemInstance : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	USukItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMesh> Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D>  ItemImage;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<class USukItemAbilityComponent> ItemAbility;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText InteractText;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetItemImage() const { return ItemImage; }
};
