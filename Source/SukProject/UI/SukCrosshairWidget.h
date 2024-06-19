// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/SukUserWidget.h"
#include "SukCrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukCrosshairWidget : public USukUserWidget
{
	GENERATED_BODY()
public:
	USukCrosshairWidget(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void NativeConstruct() override;


protected:
	UPROPERTY()
	TObjectPtr<class UImage> MainCrosshair;

	UPROPERTY()
	TObjectPtr<class UImage> HitCrosshair;

};
