// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SukHUDWidget.generated.h"

class USukHpWidget;
/**
 * 
 */
UCLASS()
class SUKPROJECT_API USukHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	USukHUDWidget(const FObjectInitializer& ObjectInitializer);

	void UpdateHpBar(float InCurrentHp, float InMaxHp);

	void CrosshairShowHit();

protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
	TObjectPtr<USukHpWidget> HpBar;

	UPROPERTY()
	TObjectPtr<class USukCrosshairWidget> Crosshair;
};
