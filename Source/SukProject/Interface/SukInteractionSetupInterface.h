// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SukInteractionSetupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USukInteractionSetupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SUKPROJECT_API ISukInteractionSetupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InteractionSetup() = 0;
	virtual void InteractionFinish() = 0;
};
