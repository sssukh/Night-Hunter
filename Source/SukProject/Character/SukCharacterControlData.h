// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SukCharacterControlData.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukCharacterControlData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	USukCharacterControlData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = State)
	uint8 bIsHoldingWeapon : 1;
};
