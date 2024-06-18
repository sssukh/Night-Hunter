// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SukWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
protected:
	virtual void InitWidget() override;
};
