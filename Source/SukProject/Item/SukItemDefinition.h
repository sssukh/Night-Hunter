// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SukItemDefinition.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukItemDefinition : public UObject
{
	GENERATED_BODY()
public:
	USukItemDefinition(const FObjectInitializer ObjectInitializer);

	UPROPERTY()
	FText DisplayName;

	
};
